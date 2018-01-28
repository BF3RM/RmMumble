// Copyright 2005-2018 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "murmur_pch.h"

#include "Server.h"
#include "ServerUser.h"
#include "Meta.h"
#include "Channel.h"

ServerUser::ServerUser(Server *p, QSslSocket *socket) : Connection(p, socket), User(), s(p) {
	sState = ServerUser::Connected;
	sUdpSocket = INVALID_SOCKET;

	memset(&saiUdpAddress, 0, sizeof(saiUdpAddress));
	memset(&saiTcpLocalAddress, 0, sizeof(saiTcpLocalAddress));

	dUDPPingAvg = dUDPPingVar = 0.0f;
	dTCPPingAvg = dTCPPingVar = 0.0f;
	uiUDPPackets = uiTCPPackets = 0;

	aiUdpFlag = 1;
	uiVersion = 0;
	bVerified = true;
	iLastPermissionCheck = -1;
	
	bOpus = false;
}

/**
 * Identity = Faction~~Squad~~IsSquadLeader
 */

bool ServerUser::IsSquadLeader()
{
    auto SplitIdentity = qsIdentity.split("~~");
	if (SplitIdentity.size() < 3) return false;

    if (SplitIdentity[2] == "1") {
        return true;
    }

    return false;
}

int ServerUser::GetSquadId()
{
    if (qsIdentity.isEmpty()) return 0;
    auto SplitIdentity = qsIdentity.split("~~");
    if (SplitIdentity.size() < 3) return 0;
    return SplitIdentity[1].toInt();
}

int ServerUser::GetFactionId()
{
    if (qsIdentity.isEmpty()) return 0;
    auto SplitIdentity = qsIdentity.split("~~");
    if (qsIdentity.size() < 3) return 0;
    return SplitIdentity[0].toInt();
}

void ServerUser::UpdateContext(std::string NewContext)
{
    if (ssContext != NewContext) {
        ssContext = NewContext;
    }
}

void ServerUser::UpdateIdentity(QString NewIdentity)
{
    if (qsIdentity != NewIdentity) {
        qsIdentity = NewIdentity;
        MoveToContextualChannel();
    }
}

Channel* ServerUser::GetContextualChannel()
{
    int ChannelId = GetFactionId() * 10 + GetSquadId();
    return s->qhChannels[ChannelId];
}

void ServerUser::MoveToContextualChannel()
{
    if (!s) return;
    auto TargetChannel = GetContextualChannel();
    if (TargetChannel == cChannel) return;
    if (TargetChannel) {
        s->setUserState(this, TargetChannel, this->bMute, this->bDeaf, this->bSuppress, this->bPrioritySpeaker, this->qsName, this->qsComment);
    }
}

ServerUser::operator QString() const {
	return QString::fromLatin1("%1:%2(%3)").arg(qsName).arg(uiSession).arg(iId);
}
BandwidthRecord::BandwidthRecord() {
	iRecNum = 0;
	iSum = 0;
	for (int i=0;i<N_BANDWIDTH_SLOTS;i++)
		a_iBW[i] = 0;
}

bool BandwidthRecord::addFrame(int size, int maxpersec) {
	QMutexLocker ml(&qmMutex);

	quint64 elapsed = a_qtWhen[iRecNum].elapsed();

	if (elapsed == 0)
		return false;

	int nsum = iSum-a_iBW[iRecNum]+size;
	int bw = static_cast<int>((nsum * 1000000LL) / elapsed);

	if (bw > maxpersec)
		return false;

	a_iBW[iRecNum] = static_cast<unsigned short>(size);
	a_qtWhen[iRecNum].restart();

	iSum = nsum;

	iRecNum++;
	if (iRecNum == N_BANDWIDTH_SLOTS)
		iRecNum = 0;

	return true;
}

int BandwidthRecord::onlineSeconds() const {
	QMutexLocker ml(&qmMutex);

	return static_cast<int>(tFirst.elapsed() / 1000000LL);
}

int BandwidthRecord::idleSeconds() const {
	QMutexLocker ml(&qmMutex);

	quint64 iIdle = a_qtWhen[(iRecNum + N_BANDWIDTH_SLOTS - 1) % N_BANDWIDTH_SLOTS].elapsed();
	if (tIdleControl.elapsed() < iIdle)
		iIdle = tIdleControl.elapsed();

	return static_cast<int>(iIdle / 1000000LL);
}

void BandwidthRecord::resetIdleSeconds() {
	QMutexLocker ml(&qmMutex);

	tIdleControl.restart();
}

int BandwidthRecord::bandwidth() const {
	QMutexLocker ml(&qmMutex);

	int sum = 0;
	int records = 0;
	quint64 elapsed = 0ULL;

	for (int i=1;i<N_BANDWIDTH_SLOTS;++i) {
		int idx = (iRecNum + N_BANDWIDTH_SLOTS - i) % N_BANDWIDTH_SLOTS;
		quint64 e = a_qtWhen[idx].elapsed();
		if (e > 1000000ULL) {
			break;
		} else {
			++records;
			sum += a_iBW[idx];
			elapsed = e;
		}
	}

	if (elapsed < 250000ULL)
		return 0;

	return static_cast<int>((sum * 1000000ULL) / elapsed);
}


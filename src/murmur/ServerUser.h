// Copyright 2005-2019 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_MURMUR_SERVERUSER_H_
#define MUMBLE_MURMUR_SERVERUSER_H_

#include <QtCore/QStringList>

#ifdef Q_OS_UNIX
#include <sys/socket.h>
#else
#include <winsock2.h>
#endif

// <chrono> was introduced in C++11
#if __cplusplus >= 199711LL
#include <chrono>
#else
#include <ctime>
#endif

#include "Connection.h"
#include "Timer.h"
#include "User.h"
#include "HostAddress.h"
#include "Mumble.pb.h"

// Unfortunately, this needs to be "large enough" to hold
// enough frames to account for both short-term and
// long-term "maladjustments".

#define N_BANDWIDTH_SLOTS 360

struct BandwidthRecord
{
    int iRecNum;
    int iSum;
    Timer tFirst;
    Timer tIdleControl;
    unsigned short a_iBW[N_BANDWIDTH_SLOTS];
    Timer a_qtWhen[N_BANDWIDTH_SLOTS];
    mutable QMutex qmMutex;

    BandwidthRecord();
    bool addFrame(int size, int maxpersec);
    int onlineSeconds() const;
    int idleSeconds() const;
    void resetIdleSeconds();
    int bandwidth() const;
};

struct WhisperTarget
{
    struct Channel
    {
        int iId;
        bool bChildren;
        bool bLinks;
        QString qsGroup;
    };
    QList<unsigned int> qlSessions;
    QList<WhisperTarget::Channel> qlChannels;
    MumbleProto::VoiceTarget::RmTarget m_RmTarget = MumbleProto::VoiceTarget_RmTarget::VoiceTarget_RmTarget_Mumble;
    uint32_t m_RmTargetId = 0;
};

struct RmPlayerPosition
{
    float X = 0.f;
    float Y = 0.f;
    float Z = 0.f;

    RmPlayerPosition(float X = 0.f, float Y = 0.f, float Z = 0.f) :
        X(X), Y(Y), Z(Z) {}
};

class Server;

#if __cplusplus > 199711L
typedef std::chrono::time_point<std::chrono::steady_clock> time_point;
#else
typedef clock_t time_point;
#endif

// Simple algorithm for rate limiting
class LeakyBucket
{
private:
    unsigned int tokensPerSec, maxTokens;
    long currentTokens;
    time_point lastUpdate;

public:
    // Returns true if packets should be dropped
    bool ratelimit(int tokens);

    LeakyBucket(unsigned int tokensPerSec, unsigned int maxTokens);
};

struct PerUserData
{
    std::string m_FromUser = "";
    bool m_IsSquadLeader = false;
    int32_t m_SquadId = 0;
    int32_t m_TeamId = 0;
    std::chrono::steady_clock::time_point m_LastUpdateTime;
};

class ServerUser : public Connection, public User
{
private:
    Q_OBJECT
    Q_DISABLE_COPY(ServerUser)
public:
    void UpdateContext(std::string NewContext);
    void UpdateIdentity(QString NewIdentity);
    void UpdateSharedIdentity();
    bool IsSquadLeader();
    inline const bool HasSquad()
    {
        return GetSquadId() != 0;
    }
    int GetSquadId();
    int GetFactionId();
    void MoveToContextualChannel();
    Channel* GetContextualChannel();
protected:
    Server *s;
    int m_TeamId = 0;
    int m_SquadId = 0;
    bool m_IsSquadLeader = false;
public:
    // This is a cache of what people think this user should be
    // It is feed from all the clients, the server then decides where to
    // move the player based on what the most voted option is
    std::map<QString /** Whom from */, PerUserData /* What squad, team should be in */> m_PerUserData;
    RmPlayerPosition PlayerPosition;
    enum State { Connected, Authenticated };
    State sState;
    operator QString() const;

    float dUDPPingAvg, dUDPPingVar;
    float dTCPPingAvg, dTCPPingVar;
    quint32 uiUDPPackets, uiTCPPackets;

    unsigned int uiVersion;
    QString qsRelease;
    QString qsOS;
    QString qsOSVersion;

    std::string ssContext;
    QString qsIdentity;

    bool bVerified;
    QStringList qslEmail;

    HostAddress haAddress;

    /// Holds whether the user is using TCP
    /// or UDP for voice packets.
    ///
    /// If the flag is 0, the user is using
    /// TCP.
    ///
    /// If the flag is 1, the user is using
    /// UDP.
    QAtomicInt aiUdpFlag;

    QList<int> qlCodecs;
    bool bOpus;

    QStringList qslAccessTokens;

    QMap<int, WhisperTarget> qmTargets;
    typedef QPair<QSet<ServerUser *>, QSet<ServerUser *> > TargetCache;
    QMap<int, TargetCache> qmTargetCache;
    QMap<QString, QString> qmWhisperRedirect;

    LeakyBucket leakyBucket;

    int iLastPermissionCheck;
    QMap<int, unsigned int> qmPermissionSent;
#ifdef Q_OS_UNIX
    int sUdpSocket;
#else
    SOCKET sUdpSocket;
#endif
    BandwidthRecord bwr;
    struct sockaddr_storage saiUdpAddress;
    struct sockaddr_storage saiTcpLocalAddress;
    ServerUser(Server *parent, QSslSocket *socket);
};

#endif

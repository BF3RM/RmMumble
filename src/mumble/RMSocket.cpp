#include "qnetworkaccessmanager.h"
#include "MainWindow.h"
#include "Global.h"
#include "RMSocket.h"
#include "RMMessage.h"
#include <QTcpServer> 
#include <iostream>
#include <QTcpSocket>
#include <qtimer.h>

void RMSocket::run()
{
	QTcpServer Server;
	if (!Server.listen(QHostAddress::Any, 64304)) {
        return;
    }

    while (true) {
        Server.waitForNewConnection(-1);
        Socket = Server.nextPendingConnection();

        if (!Socket) continue;

        emit OnConnected();
		g.mw->setStatusLeft("Socket Connected");

		QTimer* RmPingTimeout = new QTimer();
		RmPingTimeout->start(11000);

		uint32_t DataSize = 0;
        qint64 Status = 0;

        while (RmPingTimeout->remainingTime() > 0 && Socket && Socket->isValid()) {
			if (Socket->waitForReadyRead(1) && Socket->bytesAvailable() > 0)
			{
				RmPingTimeout->start(11000);

				while (Socket->bytesAvailable() > 0) {
					Status = Socket->read((char*)&DataSize, sizeof(uint32_t));
					if (Status == -1) break;
					if (Status > 0 && DataSize > 256)
					{
						//qDebug() << QString("Data size exceed limit (%1)").arg(DataSize);
						DataSize = 0;
						continue;
					}
					if (Status > 0 && DataSize > 0) {
						auto Data = (char*)malloc(DataSize);
						Status = Socket->read(Data, DataSize);
						if (Status > 0)
						{
							auto Message = NewMessage((EMessageType)Data[0]);
							Message->AddData((void*)&Data[sizeof(EMessageType)], DataSize - sizeof(EMessageType));

							for (auto& Listener : MessageCallbacks[Message->GetMessageType()]) {
								Listener(Message);
							}

							// Some stuff needs to happen in the main thread, so we use qt signals to automate this
							switch (Message->GetMessageType()) {
							case EMessageType::Uuid:
								emit OnUuidReceived(QString::fromUtf8((char*)Message->GetData()));
								break;
							case EMessageType::MuteAndDeaf:
								emit OnMuteAndDeaf(*(bool*)(Message->GetData()), *(bool*)(Message->GetData()));
								break;
							default: break;
							}

							delete Message;
						}
						free(Data);
					}
				}
			}
			if (MessagePool.size() > 0)
			{
				if (auto Message = GetPoolMessage())
				{
					Socket->write(Message->m_Data, Message->GetRealSize());
					Socket->waitForBytesWritten(-1);
				}
			}
        }

		delete RmPingTimeout;
        if (Socket) Socket->deleteLater();
        emit OnDisconnected();
		g.mw->setStatusLeft("Socket Disconnected");
		g.mw->setStatusMid("...");
	}
}

class RMMessage* RMSocket::GetPoolMessage()
{
	MessagePoolLock.lock();
	if (MessagePool.empty())
	{
		return nullptr;
	}

	auto Message = *MessagePool.begin();
	MessagePool.erase(MessagePool.begin());

	MessagePoolLock.unlock();
	return Message;
}

RMMessage* RMSocket::NewMessage(EMessageType Type)
{
    return new RMMessage(this, Type);
}

void RMSocket::AddListener(OnMessageCallback Listener, EMessageType Type)
{
    MessageCallbacks[Type].push_back(Listener);
}

void RMSocket::AddMessageToPoll(class RMMessage* Message)
{
	MessagePoolLock.lock();
	MessagePool.push_back(Message);
	MessagePoolLock.unlock();
}

void RMSocket::Stop()
{
	MessagePoolLock.lock();
	Socket->disconnect();
	g.mw->setStatusLeft("Socket Disconnected");
	g.mw->setStatusMid("...");
	Socket->close();
	MessagePoolLock.unlock();
}

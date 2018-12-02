#include "RMSocket.h"
#include "RMMessage.h"
#include <QTcpServer> 
#include <iostream>

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

		uint32_t DataSize = 0;
        qint64 Status = 0;

        while (Socket && Socket->isValid()) {
            if(Socket->waitForReadyRead(-1)) {
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
						free (Data);
                    }
                }
            } else break;
        }

        if (Socket) Socket->deleteLater();
        emit OnDisconnected();
    }
}

RMMessage* RMSocket::NewMessage(EMessageType Type)
{
    return new RMMessage(Socket, Type);
}

void RMSocket::AddListener(OnMessageCallback Listener, EMessageType Type)
{
    MessageCallbacks[Type].push_back(Listener);
}
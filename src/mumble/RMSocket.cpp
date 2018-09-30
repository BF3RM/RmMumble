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

        auto Data = (char*) malloc(64);
        memset(Data, '\0', 64);
        
        qint64 Status = 0;

        while (Socket && Socket->isValid()) {
            if(Socket->waitForReadyRead(-1)) {
                while (Socket->bytesAvailable() > 0) {
                    Status = Socket->read(Data, 64);
                    if (Status == -1 || Data[0] == '\n') break;
                    if (Status > 0) {
                        auto Message = NewMessage(63);
                        memcpy(Message->Data, &Data[1], 63);
                        Message->DataSize = Status - 1; // Ignoring the 0x0 at the end

                        // Eventually removing 0xa
                        if (Message->Data[Status - 2] == 0xa) {
                            Message->Data[Status - 2] = '\0';
                            Message->DataSize --;
                        }

                        for (auto& Listener : MessageCallbacks[(EMessageType)(uint8_t)Data[0]]) {
                            Listener(Message);
                        }

                        // Some stuff needs to happen in the main thread, so we use qt signals to automate this
                        switch((EMessageType)Data[0]) {
                            case EMessageType::Uuid:
                                emit OnUuidReceived(QString::fromUtf8(Message->Data));
                            default: break;
                        }

                        delete Message;
                    }
                    memset(Data, '\0', 64);
                }
            } else break;
        }

        if (Socket) Socket->deleteLater();
        emit OnDisconnected();
    }
}

RMMessage* RMSocket::NewMessage(size_t MessageSize)
{
    return new RMMessage(Socket, MessageSize);
}

void RMSocket::AddListener(OnMessageCallback Listener, EMessageType Type)
{
    MessageCallbacks[Type].push_back(Listener);
}
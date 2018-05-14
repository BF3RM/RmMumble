#include "RMSocket.h"
#include "RMMessage.h"
#include <QTcpServer> 
#include <string>

inline std::wstring convert( const std::string& as )
{
    wchar_t* buf = new wchar_t[as.size() * 2 + 2];
    swprintf( buf, L"%S", as.c_str() );
    std::wstring rval = buf;
    delete[] buf;
    return rval;
}

void RMSocket::run()
{
    QTcpServer Server;
	if (!Server.listen(QHostAddress::Any, 64304)) {
        return;
    }

    while (true) {
        Server.waitForNewConnection(-1);
        Socket = Server.nextPendingConnection();

        auto Data = (char*) malloc(64);
        memset(Data, '\0', 64);
        
        qint64 Status = 0;

        while (Socket && Socket->isValid()) {
            if(Socket->waitForReadyRead(-1)) {
                while (Socket->bytesAvailable() > 0) {
                    Status = Socket->read(Data, 64);
                    if (Status == -1 || Data[0] == '\n') break;
                    if (Status > 0) {
                        if (Data[0] == 123 && strncmp("Ping", &Data[1], 4) == 0) {
                            Socket->write("Pong", 4);
                        }
                    }

                    auto Message = NewMessage(63);
                    memcpy(Message->Data, &Data[1], 63);
                    for (auto& Listener : MessageCallbacks[(EMessageType)(uint8_t)Data[0]]) {
                        Listener(Message);
                    }
                    delete Message;
                }
            } else break;
        }

        if (Socket) Socket->deleteLater();
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
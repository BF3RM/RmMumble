#ifndef RMMESSAGE_H
#define RMMESSAGE_H

#include <QTcpSocket> 

typedef std::function<void(class RMMessage*)> OnMessageCallback;

class RMMessage
{
public:
    RMMessage(QTcpSocket* Socket, size_t DataSize = 64) : Data(nullptr), DataSize(DataSize), Socket(Socket)
    {
        Data = (char*) malloc(DataSize);
        memset(&Data[0], '\0', 64);
    }

    ~RMMessage()
    {
        free(Data);
    }

    void Send()
    {
        Socket->write(&Data[0], DataSize);
    }
public:
    char* Data;
    size_t DataSize;
protected:
    QTcpSocket* Socket;
};

#endif
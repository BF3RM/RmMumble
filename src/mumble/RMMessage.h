#include <QTcpSocket> 

class RMMessage
{
public:
    RMMessage(QTcpSocket* Socket, size_t DataSize = 64) : Socket(Socket), DataSize(DataSize)
    {
        memset(&Data[0], '\0', 64);
        Data = (char*) malloc(DataSize);
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
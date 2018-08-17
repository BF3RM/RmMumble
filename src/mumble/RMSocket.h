#ifndef RMSOCKET_H
#define RMSOCKET_H

#include <QThread>
#include <map>
#include <vector>
#include "RMMessage.h"


enum class EMessageType : uint8_t
{
    StopTalking = 121,
    Talking = 122,
    Uuid = 123,
    Ping = 124
};

class RMSocket : public QThread
{
    Q_OBJECT
public:
    RMSocket() : Socket(nullptr) {}
    RMMessage* NewMessage(size_t MessageSize = 64);
    void AddListener(OnMessageCallback Listener, EMessageType Type);
    inline bool IsAlive() { return Socket != nullptr; };
    inline QTcpSocket* GetSocket() { return Socket; }
protected:
    void run() override;
protected:
    class QTcpSocket* Socket;
    std::map<EMessageType, std::vector<OnMessageCallback>> MessageCallbacks;
signals:
    void OnUuidReceived(QString Uuid);
};

#endif
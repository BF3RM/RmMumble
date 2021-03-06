#ifndef RMSOCKET_H
#define RMSOCKET_H

#include <QThread>
#include <map>
#include <vector>
#include <QMutex>

#include "RMMessage.h"

class RMSocket : public QThread
{
    Q_OBJECT
public:
    RMSocket() : Socket(nullptr) {}
    RMMessage* NewMessage(EMessageType Type);
    void AddListener(OnMessageCallback Listener, EMessageType Type);
    inline bool IsAlive()
    {
        return Socket != nullptr;
    }
    inline class QTcpSocket* GetSocket()
    {
        return Socket;
    }
    void AddMessageToPoll(class RMMessage* Message);
    void Stop();
protected:
    void run() override;
protected:
    class RMMessage* GetPoolMessage();
    class QTcpSocket* Socket;
    std::map<EMessageType, std::vector<OnMessageCallback>> MessageCallbacks;
signals:
    void OnUuidReceived(QString Uuid);
    void OnHostAndPortReceived(QString Uuid);
    void OnMuteAndDeaf(bool Mute, bool Deaf);
    void OnDisconnected();
    void OnConnected();

protected:
    std::vector<class RMMessage*> MessagePool;
    QMutex MessagePoolLock;
    bool bShouldBeDestroyed = false;
};

#endif
#ifndef RMSOCKET_H
#define RMSOCKET_H

#include <QThread>
#include <map>
#include <vector>

#include "RMMessage.h"

class RMSocket : public QThread
{
    Q_OBJECT
public:
    RMSocket() : Socket(nullptr) {}
    RMMessage* NewMessage(EMessageType Type);
    void AddListener(OnMessageCallback Listener, EMessageType Type);
    inline bool IsAlive() { return Socket != nullptr; }
    inline class QTcpSocket* GetSocket() { return Socket; }
	void AddMessageToPoll(class RMMessage* Message);
protected:
    void run() override;
protected:
	class RMMessage* GetPoolMessage();
    class QTcpSocket* Socket;
    std::map<EMessageType, std::vector<OnMessageCallback>> MessageCallbacks;
signals:
    void OnUuidReceived(QString Uuid);
    void OnMuteAndDeaf(bool Mute, bool Deaf);
    void OnDisconnected();
    void OnConnected();

protected:
	std::vector<class RMMessage*> MessagePool;
	std::mutex MessagePoolLock;
};

#endif
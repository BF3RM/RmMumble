#include <QThread>
#include <map>
#include <vector>

typedef std::function<void(class RMMessage*)> OnMessageCallback;

enum class EMessageType : uint8_t
{
    Uuid = 123,
    Ping = 124
};

class RMSocket : public QThread
{
    Q_OBJECT
public:
    RMSocket() : Socket(nullptr) {}
    class RMMessage* NewMessage(size_t MessageSize = 64);
    void AddListener(OnMessageCallback Listener, EMessageType Type);
protected:
    void run() override;
protected:
    class QTcpSocket* Socket;
    std::map<EMessageType, std::vector<OnMessageCallback>> MessageCallbacks;
};
#include <QObject>

class Rm3DSocket : public QObject
{
public:
    Rm3DSocket(QObject* Parent);
    const float* GetPawnPosition() const;
    const float* GetPawnFrontVector() const;
    const float* GetPawnTopVector() const;
protected:
    void OnDataAvailable();
protected:
    class QUdpSocket* m_UdpSocket = nullptr;
    float m_PawnPosition[3] = { 0x0 };
    float m_PawnFrontVector[3] = { 0x0 };
    float m_PawnTopVector[3] = { 0x0 };
};
#include "Rm3DSocket.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "Global.h"
#include "MainWindow.h"

Rm3DSocket::Rm3DSocket(QObject* Parent) : QObject(Parent)
{
    m_UdpSocket = new QUdpSocket(g.mw);
    m_UdpSocket->bind(QHostAddress::LocalHost, 55778);
    connect(m_UdpSocket, &QUdpSocket::readyRead, this, &Rm3DSocket::OnDataAvailable);
}

void Rm3DSocket::OnDataAvailable()
{
    while (m_UdpSocket->hasPendingDatagrams())
    {
        QNetworkDatagram Datagram = m_UdpSocket->receiveDatagram();
        auto Offset = sizeof(float) * 3;
        if (Datagram.data().size() == Offset * 3)
        {
            memcpy(m_PawnPosition, Datagram.data().constData(), Offset);
            memcpy(m_PawnFrontVector, Datagram.data().constData() + Offset, Offset);
            memcpy(m_PawnTopVector, Datagram.data().constData() + Offset * 2, Offset);
        }
    }

}

const float* Rm3DSocket::GetPawnPosition() const
{
    return m_PawnPosition;
}

const float* Rm3DSocket::GetPawnFrontVector() const
{
    return m_PawnFrontVector;
}

const float* Rm3DSocket::GetPawnTopVector() const
{
    return m_PawnTopVector;
}

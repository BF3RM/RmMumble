//
// Created by skaya on 08/11/18.
//

#ifndef PR_MUMBLE_SERVERRESOLVERPRIVATE_H
#define PR_MUMBLE_SERVERRESOLVERPRIVATE_H

#include <QtCore/QObject>
#include "ServerResolverRecord.h"
#include <QtNetwork/QDnsLookup>
#include <QtNetwork/QHostInfo>

class ServerResolverPrivate : public QObject
{
private:
    Q_OBJECT
    Q_DISABLE_COPY(ServerResolverPrivate)
public:
    ServerResolverPrivate(QObject *parent);

    void resolve(QString hostname, quint16 port);
    QList<ServerResolverRecord> records();

    QString m_origHostname;
    quint16 m_origPort;

    QList<QDnsServiceRecord> m_srvQueue;
    QMap<int, int> m_hostInfoIdToIndexMap;
    int m_srvQueueRemain;

    QList<ServerResolverRecord> m_resolved;

signals:
    void resolved();

public slots:
    void srvResolved();
    void hostResolved(QHostInfo hostInfo);
    void hostFallbackResolved(QHostInfo hostInfo);
};


#endif //PR_MUMBLE_SERVERRESOLVERPRIVATE_H

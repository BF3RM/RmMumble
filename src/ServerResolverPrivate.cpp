//
// Created by skaya on 08/11/18.
//

#include "ServerResolverPrivate.h"

static qint64 normalizeSrvPriority(quint16 priority, quint16 weight) {
    return static_cast<qint64>((65535U * priority) + weight);
}


ServerResolverPrivate::ServerResolverPrivate(QObject *parent)
        : QObject(parent)
        , m_origPort(0)
        , m_srvQueueRemain(0) {
}

void ServerResolverPrivate::resolve(QString hostname, quint16 port) {
    m_origHostname = hostname;
    m_origPort = port;

    QDnsLookup *resolver = new QDnsLookup(this);
    connect(resolver, SIGNAL(finished()), this, SLOT(srvResolved()));
    resolver->setType(QDnsLookup::SRV);

    resolver->setName(QLatin1String("_mumble._tcp.") + hostname);
    resolver->lookup();
}

QList<ServerResolverRecord> ServerResolverPrivate::records() {
    return m_resolved;
}

void ServerResolverPrivate::srvResolved() {
    QDnsLookup *resolver = qobject_cast<QDnsLookup *>(sender());

    m_srvQueue = resolver->serviceRecords();
    m_srvQueueRemain = m_srvQueue.count();

    if (resolver->error() == QDnsLookup::NoError && m_srvQueueRemain > 0) {
        for (int i = 0; i < m_srvQueue.count(); i++) {
            QDnsServiceRecord record = m_srvQueue.at(i);
            int hostInfoId = QHostInfo::lookupHost(record.target(), this, SLOT(hostResolved(QHostInfo)));
            m_hostInfoIdToIndexMap[hostInfoId] = i;
        }
    } else {
        QHostInfo::lookupHost(m_origHostname, this, SLOT(hostFallbackResolved(QHostInfo)));
    }

    delete resolver;
}

void ServerResolverPrivate::hostResolved(QHostInfo hostInfo) {
    int lookupId = hostInfo.lookupId();
    int idx = m_hostInfoIdToIndexMap[lookupId];
    QDnsServiceRecord record = m_srvQueue.at(idx);

    if (hostInfo.error() == QHostInfo::NoError) {
        QList<QHostAddress> resolvedAddresses = hostInfo.addresses();

        // Convert QHostAddress -> HostAddress.
        QList<HostAddress> addresses;
        foreach (QHostAddress ha, resolvedAddresses) {
            addresses << HostAddress(ha);
        }

        qint64 priority = normalizeSrvPriority(record.priority(), record.weight());
        m_resolved << ServerResolverRecord(m_origHostname, record.port(), priority, addresses);
    }

    m_srvQueueRemain -= 1;
    if (m_srvQueueRemain == 0) {
        emit resolved();
    }
}

void ServerResolverPrivate::hostFallbackResolved(QHostInfo hostInfo) {
    if (hostInfo.error() == QHostInfo::NoError) {
        QList<QHostAddress> resolvedAddresses = hostInfo.addresses();

        // Convert QHostAddress -> HostAddress.
        QList<HostAddress> addresses;
        foreach (QHostAddress ha, resolvedAddresses) {
            addresses << HostAddress(ha);
        }

        m_resolved << ServerResolverRecord(m_origHostname, m_origPort, 0, addresses);
    }

    emit resolved();
}

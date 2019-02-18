// Copyright 2005-2019 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "murmur_pch.h"

#include "ServerResolver.h"
#include "ServerResolverPrivate.h"

#include <QtNetwork/QDnsLookup>
#include <QtNetwork/QHostInfo>

ServerResolver::ServerResolver(QObject *parent)
	: QObject(parent) {

	d = new ServerResolverPrivate(this);
}

QString ServerResolver::hostname() {
	if (d) {
		return d->m_origHostname;
	}

	return QString();
}

quint16 ServerResolver::port() {
	if (d) {
		return d->m_origPort;
	}

	return 0;
}

void ServerResolver::resolve(QString hostname, quint16 port) {
	if (d) {
		connect(d, SIGNAL(resolved()), this, SIGNAL(resolved()));
		d->resolve(hostname, port);
	}
}

QList<ServerResolverRecord> ServerResolver::records() {
	if (d) {
		return d->records();
	}
	return QList<ServerResolverRecord>();
}


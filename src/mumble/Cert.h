// Copyright 2005-2019 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_MUMBLE_CERT_H_
#define MUMBLE_MUMBLE_CERT_H_

#include <QtCore/QtGlobal>
#include <QtCore/QString>
#if QT_VERSION >= 0x050000
# include <QtWidgets/QGroupBox>
#else
# include <QtGui/QGroupBox>
#endif

#include <QtNetwork/QHostInfo>
#include <QtNetwork/QSslCertificate>

#include "Settings.h"

class QLabel;
class QWidget;

class CertView : public QGroupBox
{
private:
    Q_OBJECT
    Q_DISABLE_COPY(CertView)
protected:
    QList<QSslCertificate> qlCert;
    QLabel *qlSubjectName, *qlSubjectEmail, *qlIssuerName, *qlExpiry;
public:
    CertView(QWidget *p);
    void setCert(const QList<QSslCertificate> &cert);
};

#include "ui_Cert.h"

class CertWizard : public QWizard, public Ui::Certificates
{
private:
    Q_OBJECT
    Q_DISABLE_COPY(CertWizard)
protected:
    Settings::KeyPair kpCurrent, kpNew;
public:
    CertWizard(QWidget *p = NULL);
    int nextId() const Q_DECL_OVERRIDE;
    void initializePage(int) Q_DECL_OVERRIDE;
    bool validateCurrentPage() Q_DECL_OVERRIDE;
    static bool validateCert(const Settings::KeyPair &);
    static Settings::KeyPair generateNewCert(QString name = QString(), const QString &email = QString());
    static QByteArray exportCert(const Settings::KeyPair &cert);
    static Settings::KeyPair importCert(QByteArray, const QString & = QString());
public slots:
    void on_qleEmail_textChanged(const QString &);
    void on_qpbExportFile_clicked();
    void on_qleExportFile_textChanged(const QString &);
    void on_qpbImportFile_clicked();
    void on_qleImportFile_textChanged(const QString &);
    void on_qlePassword_textChanged(const QString &);
    void on_qlIntroText_linkActivated(const QString &);
};

#endif

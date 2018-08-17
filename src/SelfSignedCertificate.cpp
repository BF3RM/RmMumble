// Copyright 2005-2018 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "murmur_pch.h"

#include "SelfSignedCertificate.h"

#define SSL_STRING(x) QString::fromLatin1(x).toUtf8().data()

static int add_ext(X509 * crt, int nid, char *value) {
	X509V3_CTX ctx;
	X509V3_set_ctx_nodb(&ctx);
	X509V3_set_ctx(&ctx, crt, crt, NULL, NULL, 0);

	X509_EXTENSION *ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);
	if (ex == NULL) {
		return 0;
	}

	if (X509_add_ext(crt, ex, -1) == 0) {
		X509_EXTENSION_free(ex);
		return 0;
	}

	X509_EXTENSION_free(ex);
	return 1;
}

bool SelfSignedCertificate::generate(QString clientCertName, QString clientCertEmail, QSslCertificate &qscCert, QSslKey &qskKey) {
	bool ok = true;
	X509 *x509 = NULL;
	EVP_PKEY *pkey = NULL;
	RSA *rsa = NULL;
	BIGNUM *e = NULL;
	X509_NAME *name = NULL;
	ASN1_INTEGER *serialNumber = NULL;
	ASN1_TIME *notBefore = NULL;
	ASN1_TIME *notAfter = NULL;
	QString commonName;
	bool isServerCert = clientCertName.isEmpty() && clientCertEmail.isEmpty();

	if (CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON) == -1) {
		ok = false;
		goto out;
	}

	x509 = X509_new();
	if (x509 == NULL) {
		ok = false;
		goto out;
	}

	pkey = EVP_PKEY_new();
	if (pkey == NULL) {
		ok = false;
		goto out;
	}

	rsa = RSA_new();
	if (rsa == NULL) {
		ok = false;
		goto out;
	}

	e = BN_new();
	if (e == NULL) {
		ok = false;
		goto out;
	}
	if (BN_set_word(e, 65537) == 0) {
		ok = false;
		goto out;
	}

	if (RSA_generate_key_ex(rsa, 2048, e, NULL) == 0) {
		ok = false;
		goto out;
	}

	if (EVP_PKEY_assign_RSA(pkey, rsa) == 0) {
		ok = false;
		goto out;
	}

	if (X509_set_version(x509, 2) == 0) {
		ok = false;
		goto out;
	}

	serialNumber = X509_get_serialNumber(x509);
	if (serialNumber == NULL) {
		ok = false;
		goto out;
	}
	if (ASN1_INTEGER_set(serialNumber, 1) == 0) {
		ok = false;
		goto out;
	}

	notBefore = X509_get_notBefore(x509);
	if (notBefore == NULL) {
		ok = false;
		goto out;
	}
	if (X509_gmtime_adj(notBefore, 0) == NULL) {
		ok = false;
		goto out;
	}

	notAfter = X509_get_notAfter(x509);
	if (notAfter == NULL) {
		ok = false;
		goto out;
	}
	if (X509_gmtime_adj(notAfter, 60*60*24*365*20) == NULL) {
		ok = false;
		goto out;
	}

	if (X509_set_pubkey(x509, pkey) == 0) {
		ok = false;
		goto out;
	}

	name = X509_get_subject_name(x509);
	if (name == NULL) {
		ok = false;
		goto out;
	}

	if (isServerCert) {
		commonName = QLatin1String("Murmur Autogenerated Certificate v2");
	} else {
		if (!clientCertName.isEmpty()) {
			commonName = clientCertName;
		} else {
			commonName = QLatin1String("Mumble User");
		}
	}

	if (X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, reinterpret_cast<unsigned char *>(commonName.toUtf8().data()), -1, -1, 0) == 0) {
		ok = false;
		goto out;
	}

	if (X509_set_issuer_name(x509, name) == 0) {
		ok = false;
		goto out;
	}

	if (add_ext(x509, NID_basic_constraints, SSL_STRING("critical,CA:FALSE")) == 0) {
		ok = false;
		goto out;
	}

	if (isServerCert) {
		if (add_ext(x509, NID_ext_key_usage, SSL_STRING("serverAuth,clientAuth")) == 0) {
			ok = false;
			goto out;
		}
	} else {
		if (add_ext(x509, NID_ext_key_usage, SSL_STRING("clientAuth")) == 0) {
			ok = false;
			goto out;
		}
	}

	if (add_ext(x509, NID_subject_key_identifier, SSL_STRING("hash")) == 0) {
		ok = false;
		goto out;
	}

	if (isServerCert) {
		if (add_ext(x509, NID_netscape_comment, SSL_STRING("Generated from murmur")) == 0) {
			ok = false;
			goto out;
		}
	} else {
		if (add_ext(x509, NID_netscape_comment, SSL_STRING("Generated by Mumble")) == 0) {
			ok = false;
			goto out;
		}
	}

	if (!isServerCert) {
		if (add_ext(x509, NID_subject_alt_name, QString::fromLatin1("email:%1").arg(clientCertEmail).toUtf8().data()) == 0) {
			ok = false;
			goto out;
		}
	}

	if (X509_sign(x509, pkey, EVP_sha1()) == 0) {
		ok = false;
		goto out;
	}

	{
		QByteArray crt;
		int len = i2d_X509(x509, NULL);
		if (len <= 0) {
			ok = false;
			goto out;
		}
		crt.resize(len);

		unsigned char *dptr = reinterpret_cast<unsigned char *>(crt.data());
		if (i2d_X509(x509, &dptr) != len) {
			ok = false;
			goto out;
		}

		qscCert = QSslCertificate(crt, QSsl::Der);
		if (qscCert.isNull()) {
			ok = false;
		}
	}

	{
		QByteArray key;
		int len = i2d_PrivateKey(pkey, NULL);
		if (len <= 0) {
			ok = false;
			goto out;
		}
		key.resize(len);

		unsigned char *dptr = reinterpret_cast<unsigned char *>(key.data());
		if (i2d_PrivateKey(pkey, &dptr) != len) {
			ok = false;
			goto out;
		}

		qskKey = QSslKey(key, QSsl::Rsa, QSsl::Der);
		if (qskKey.isNull()) {
			ok = false;
		}
	}

out:
	if (e) {
		BN_free(e);
	}
	// We only need to free the pkey pointer,
	// not the RSA pointer. We have assigned
	// our RSA key to pkey, and it will be freed
	// once we free pkey.
	if (pkey) {
		EVP_PKEY_free(pkey);
	}
	if (x509) {
		X509_free(x509);
	}

	if (!ok) {
		qscCert = QSslCertificate();
		qskKey = QSslKey();
	}

	return ok;
}

bool SelfSignedCertificate::generateMumbleCertificate(QString name, QString email, QSslCertificate &qscCert, QSslKey &qskKey) {
	if (name.trimmed().isEmpty()) {
		qscCert = QSslCertificate();
		qskKey = QSslKey();
		return false;
	}
	if (email.trimmed().isEmpty()) {
		qscCert = QSslCertificate();
		qskKey = QSslKey();
		return false;
	}
	return SelfSignedCertificate::generate(name, email, qscCert, qskKey);
}

bool SelfSignedCertificate::generateMurmurV2Certificate(QSslCertificate &qscCert, QSslKey &qskKey) {
	return SelfSignedCertificate::generate(QString(), QString(), qscCert, qskKey);
}

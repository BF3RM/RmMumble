// Copyright 2005-2019 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

// Automatically generated by "generate-cipherinfo.py". DO NOT EDIT BY HAND.

static const SSLCipherInfo cipher_info_lookup_table[] =
{
    {
        // openssl_name
        "RC4-MD5",
        // rfc_name
        "TLS_RSA_WITH_RC4_128_MD5",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-MD5",
    },
    {
        // openssl_name
        "RC4-SHA",
        // rfc_name
        "TLS_RSA_WITH_RC4_128_SHA",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "IDEA-CBC-SHA",
        // rfc_name
        "TLS_RSA_WITH_IDEA_CBC_SHA",
        // encryption
        "IDEA_128_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DES-CBC3-SHA",
        // rfc_name
        "TLS_RSA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-DSS-DES-CBC3-SHA",
        // rfc_name
        "TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-RSA-DES-CBC3-SHA",
        // rfc_name
        "TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "EDH-DSS-DES-CBC3-SHA",
        // rfc_name
        "TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "EDH-RSA-DES-CBC3-SHA",
        // rfc_name
        "TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ADH-RC4-MD5",
        // rfc_name
        "TLS_DH_anon_WITH_RC4_128_MD5",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-MD5",
    },
    {
        // openssl_name
        "ADH-DES-CBC3-SHA",
        // rfc_name
        "TLS_DH_anon_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "AES128-SHA",
        // rfc_name
        "TLS_RSA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-DSS-AES128-SHA",
        // rfc_name
        "TLS_DH_DSS_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-RSA-AES128-SHA",
        // rfc_name
        "TLS_DH_RSA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-DSS-AES128-SHA",
        // rfc_name
        "TLS_DHE_DSS_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-RSA-AES128-SHA",
        // rfc_name
        "TLS_DHE_RSA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ADH-AES128-SHA",
        // rfc_name
        "TLS_DH_anon_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "AES256-SHA",
        // rfc_name
        "TLS_RSA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-DSS-AES256-SHA",
        // rfc_name
        "TLS_DH_DSS_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-RSA-AES256-SHA",
        // rfc_name
        "TLS_DH_RSA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-DSS-AES256-SHA",
        // rfc_name
        "TLS_DHE_DSS_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-RSA-AES256-SHA",
        // rfc_name
        "TLS_DHE_RSA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ADH-AES256-SHA",
        // rfc_name
        "TLS_DH_anon_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "AES128-SHA256",
        // rfc_name
        "TLS_RSA_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "AES256-SHA256",
        // rfc_name
        "TLS_RSA_WITH_AES_256_CBC_SHA256",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "DH-DSS-AES128-SHA256",
        // rfc_name
        "TLS_DH_DSS_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "DH-RSA-AES128-SHA256",
        // rfc_name
        "TLS_DH_RSA_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "DHE-DSS-AES128-SHA256",
        // rfc_name
        "TLS_DHE_DSS_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "CAMELLIA128-SHA",
        // rfc_name
        "TLS_RSA_WITH_CAMELLIA_128_CBC_SHA",
        // encryption
        "CAMELLIA_128_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-DSS-CAMELLIA128-SHA",
        // rfc_name
        "TLS_DH_DSS_WITH_CAMELLIA_128_CBC_SHA",
        // encryption
        "CAMELLIA_128_CBC",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-RSA-CAMELLIA128-SHA",
        // rfc_name
        "TLS_DH_RSA_WITH_CAMELLIA_128_CBC_SHA",
        // encryption
        "CAMELLIA_128_CBC",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-DSS-CAMELLIA128-SHA",
        // rfc_name
        "TLS_DHE_DSS_WITH_CAMELLIA_128_CBC_SHA",
        // encryption
        "CAMELLIA_128_CBC",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-RSA-CAMELLIA128-SHA",
        // rfc_name
        "TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA",
        // encryption
        "CAMELLIA_128_CBC",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ADH-CAMELLIA128-SHA",
        // rfc_name
        "TLS_DH_anon_WITH_CAMELLIA_128_CBC_SHA",
        // encryption
        "CAMELLIA_128_CBC",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-RSA-AES128-SHA256",
        // rfc_name
        "TLS_DHE_RSA_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "DH-DSS-AES256-SHA256",
        // rfc_name
        "TLS_DH_DSS_WITH_AES_256_CBC_SHA256",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "DH-RSA-AES256-SHA256",
        // rfc_name
        "TLS_DH_RSA_WITH_AES_256_CBC_SHA256",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "DHE-DSS-AES256-SHA256",
        // rfc_name
        "TLS_DHE_DSS_WITH_AES_256_CBC_SHA256",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "DHE-RSA-AES256-SHA256",
        // rfc_name
        "TLS_DHE_RSA_WITH_AES_256_CBC_SHA256",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "ADH-AES128-SHA256",
        // rfc_name
        "TLS_DH_anon_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "ADH-AES256-SHA256",
        // rfc_name
        "TLS_DH_anon_WITH_AES_256_CBC_SHA256",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "CAMELLIA256-SHA",
        // rfc_name
        "TLS_RSA_WITH_CAMELLIA_256_CBC_SHA",
        // encryption
        "CAMELLIA_256_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-DSS-CAMELLIA256-SHA",
        // rfc_name
        "TLS_DH_DSS_WITH_CAMELLIA_256_CBC_SHA",
        // encryption
        "CAMELLIA_256_CBC",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-RSA-CAMELLIA256-SHA",
        // rfc_name
        "TLS_DH_RSA_WITH_CAMELLIA_256_CBC_SHA",
        // encryption
        "CAMELLIA_256_CBC",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-DSS-CAMELLIA256-SHA",
        // rfc_name
        "TLS_DHE_DSS_WITH_CAMELLIA_256_CBC_SHA",
        // encryption
        "CAMELLIA_256_CBC",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-RSA-CAMELLIA256-SHA",
        // rfc_name
        "TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA",
        // encryption
        "CAMELLIA_256_CBC",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ADH-CAMELLIA256-SHA",
        // rfc_name
        "TLS_DH_anon_WITH_CAMELLIA_256_CBC_SHA",
        // encryption
        "CAMELLIA_256_CBC",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "PSK-RC4-SHA",
        // rfc_name
        "TLS_PSK_WITH_RC4_128_SHA",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = PSK, au = PSK
        "PSK",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "PSK-3DES-EDE-CBC-SHA",
        // rfc_name
        "TLS_PSK_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = PSK, au = PSK
        "PSK",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "PSK-AES128-CBC-SHA",
        // rfc_name
        "TLS_PSK_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = PSK, au = PSK
        "PSK",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "PSK-AES256-CBC-SHA",
        // rfc_name
        "TLS_PSK_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = PSK, au = PSK
        "PSK",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SEED-SHA",
        // rfc_name
        "TLS_RSA_WITH_SEED_CBC_SHA",
        // encryption
        "SEED_128_CBC",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-DSS-SEED-SHA",
        // rfc_name
        "TLS_DH_DSS_WITH_SEED_CBC_SHA",
        // encryption
        "SEED_128_CBC",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DH-RSA-SEED-SHA",
        // rfc_name
        "TLS_DH_RSA_WITH_SEED_CBC_SHA",
        // encryption
        "SEED_128_CBC",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-DSS-SEED-SHA",
        // rfc_name
        "TLS_DHE_DSS_WITH_SEED_CBC_SHA",
        // encryption
        "SEED_128_CBC",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "DHE-RSA-SEED-SHA",
        // rfc_name
        "TLS_DHE_RSA_WITH_SEED_CBC_SHA",
        // encryption
        "SEED_128_CBC",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ADH-SEED-SHA",
        // rfc_name
        "TLS_DH_anon_WITH_SEED_CBC_SHA",
        // encryption
        "SEED_128_CBC",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "AES128-GCM-SHA256",
        // rfc_name
        "TLS_RSA_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "AES256-GCM-SHA384",
        // rfc_name
        "TLS_RSA_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = RSA, au = RSA
        "RSA",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "DHE-RSA-AES128-GCM-SHA256",
        // rfc_name
        "TLS_DHE_RSA_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "DHE-RSA-AES256-GCM-SHA384",
        // rfc_name
        "TLS_DHE_RSA_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = DHE, au = RSA
        "DHE_RSA",
        // forward secret
        true,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "DH-RSA-AES128-GCM-SHA256",
        // rfc_name
        "TLS_DH_RSA_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "DH-RSA-AES256-GCM-SHA384",
        // rfc_name
        "TLS_DH_RSA_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = DH_RSA, au = DH
        "DH_RSA",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "DHE-DSS-AES128-GCM-SHA256",
        // rfc_name
        "TLS_DHE_DSS_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "DHE-DSS-AES256-GCM-SHA384",
        // rfc_name
        "TLS_DHE_DSS_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = DHE, au = DSS
        "DHE_DSS",
        // forward secret
        true,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "DH-DSS-AES128-GCM-SHA256",
        // rfc_name
        "TLS_DH_DSS_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "DH-DSS-AES256-GCM-SHA384",
        // rfc_name
        "TLS_DH_DSS_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = DH_DSS, au = DH
        "DH_DSS",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ADH-AES128-GCM-SHA256",
        // rfc_name
        "TLS_DH_anon_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ADH-AES256-GCM-SHA384",
        // rfc_name
        "TLS_DH_anon_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = DH, au = Anonymous
        "DH_anon",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ECDH-ECDSA-RC4-SHA",
        // rfc_name
        "TLS_ECDH_ECDSA_WITH_RC4_128_SHA",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = ECDH_ECDSA, au = ECDH
        "ECDH_ECDSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDH-ECDSA-DES-CBC3-SHA",
        // rfc_name
        "TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = ECDH_ECDSA, au = ECDH
        "ECDH_ECDSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDH-ECDSA-AES128-SHA",
        // rfc_name
        "TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDH_ECDSA, au = ECDH
        "ECDH_ECDSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDH-ECDSA-AES256-SHA",
        // rfc_name
        "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDH_ECDSA, au = ECDH
        "ECDH_ECDSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-ECDSA-RC4-SHA",
        // rfc_name
        "TLS_ECDHE_ECDSA_WITH_RC4_128_SHA",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = ECDHE, au = ECDSA
        "ECDHE_ECDSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-ECDSA-DES-CBC3-SHA",
        // rfc_name
        "TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = ECDHE, au = ECDSA
        "ECDHE_ECDSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-ECDSA-AES128-SHA",
        // rfc_name
        "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDHE, au = ECDSA
        "ECDHE_ECDSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-ECDSA-AES256-SHA",
        // rfc_name
        "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDHE, au = ECDSA
        "ECDHE_ECDSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDH-RSA-RC4-SHA",
        // rfc_name
        "TLS_ECDH_RSA_WITH_RC4_128_SHA",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = ECDH_RSA, au = ECDH
        "ECDH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDH-RSA-DES-CBC3-SHA",
        // rfc_name
        "TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = ECDH_RSA, au = ECDH
        "ECDH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDH-RSA-AES128-SHA",
        // rfc_name
        "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDH_RSA, au = ECDH
        "ECDH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDH-RSA-AES256-SHA",
        // rfc_name
        "TLS_ECDH_RSA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDH_RSA, au = ECDH
        "ECDH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-RSA-RC4-SHA",
        // rfc_name
        "TLS_ECDHE_RSA_WITH_RC4_128_SHA",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = ECDHE, au = RSA
        "ECDHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-RSA-DES-CBC3-SHA",
        // rfc_name
        "TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = ECDHE, au = RSA
        "ECDHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-RSA-AES128-SHA",
        // rfc_name
        "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDHE, au = RSA
        "ECDHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-RSA-AES256-SHA",
        // rfc_name
        "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDHE, au = RSA
        "ECDHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "AECDH-RC4-SHA",
        // rfc_name
        "TLS_ECDH_anon_WITH_RC4_128_SHA",
        // encryption
        "RC4_128",
        // key_exchange_verbose. kx = ECDH, au = Anonymous
        "ECDH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "AECDH-DES-CBC3-SHA",
        // rfc_name
        "TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = ECDH, au = Anonymous
        "ECDH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "AECDH-AES128-SHA",
        // rfc_name
        "TLS_ECDH_anon_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDH, au = Anonymous
        "ECDH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "AECDH-AES256-SHA",
        // rfc_name
        "TLS_ECDH_anon_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDH, au = Anonymous
        "ECDH_anon",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-3DES-EDE-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = SRP, au = SRP
        "SRP_SHA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-RSA-3DES-EDE-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_RSA_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = SRP, au = RSA
        "SRP_SHA_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-DSS-3DES-EDE-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_DSS_WITH_3DES_EDE_CBC_SHA",
        // encryption
        "3DES_168_EDE_CBC",
        // key_exchange_verbose. kx = SRP, au = DSS
        "SRP_SHA_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-AES-128-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = SRP, au = SRP
        "SRP_SHA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-RSA-AES-128-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_RSA_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = SRP, au = RSA
        "SRP_SHA_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-DSS-AES-128-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_DSS_WITH_AES_128_CBC_SHA",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = SRP, au = DSS
        "SRP_SHA_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-AES-256-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = SRP, au = SRP
        "SRP_SHA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-RSA-AES-256-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_RSA_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = SRP, au = RSA
        "SRP_SHA_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "SRP-DSS-AES-256-CBC-SHA",
        // rfc_name
        "TLS_SRP_SHA_DSS_WITH_AES_256_CBC_SHA",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = SRP, au = DSS
        "SRP_SHA_DSS",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA1",
    },
    {
        // openssl_name
        "ECDHE-ECDSA-AES128-SHA256",
        // rfc_name
        "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDHE, au = ECDSA
        "ECDHE_ECDSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "ECDHE-ECDSA-AES256-SHA384",
        // rfc_name
        "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDHE, au = ECDSA
        "ECDHE_ECDSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA384",
    },
    {
        // openssl_name
        "ECDH-ECDSA-AES128-SHA256",
        // rfc_name
        "TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDH_ECDSA, au = ECDH
        "ECDH_ECDSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "ECDH-ECDSA-AES256-SHA384",
        // rfc_name
        "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDH_ECDSA, au = ECDH
        "ECDH_ECDSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA384",
    },
    {
        // openssl_name
        "ECDHE-RSA-AES128-SHA256",
        // rfc_name
        "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDHE, au = RSA
        "ECDHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "ECDHE-RSA-AES256-SHA384",
        // rfc_name
        "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDHE, au = RSA
        "ECDHE_RSA",
        // forward secret
        true,
        // message authentication
        "HMAC-SHA384",
    },
    {
        // openssl_name
        "ECDH-RSA-AES128-SHA256",
        // rfc_name
        "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256",
        // encryption
        "AES_128_CBC",
        // key_exchange_verbose. kx = ECDH_RSA, au = ECDH
        "ECDH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA256",
    },
    {
        // openssl_name
        "ECDH-RSA-AES256-SHA384",
        // rfc_name
        "TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384",
        // encryption
        "AES_256_CBC",
        // key_exchange_verbose. kx = ECDH_RSA, au = ECDH
        "ECDH_RSA",
        // forward secret
        false,
        // message authentication
        "HMAC-SHA384",
    },
    {
        // openssl_name
        "ECDHE-ECDSA-AES128-GCM-SHA256",
        // rfc_name
        "TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = ECDHE, au = ECDSA
        "ECDHE_ECDSA",
        // forward secret
        true,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ECDHE-ECDSA-AES256-GCM-SHA384",
        // rfc_name
        "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = ECDHE, au = ECDSA
        "ECDHE_ECDSA",
        // forward secret
        true,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ECDH-ECDSA-AES128-GCM-SHA256",
        // rfc_name
        "TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = ECDH_ECDSA, au = ECDH
        "ECDH_ECDSA",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ECDH-ECDSA-AES256-GCM-SHA384",
        // rfc_name
        "TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = ECDH_ECDSA, au = ECDH
        "ECDH_ECDSA",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ECDHE-RSA-AES128-GCM-SHA256",
        // rfc_name
        "TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = ECDHE, au = RSA
        "ECDHE_RSA",
        // forward secret
        true,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ECDHE-RSA-AES256-GCM-SHA384",
        // rfc_name
        "TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = ECDHE, au = RSA
        "ECDHE_RSA",
        // forward secret
        true,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ECDH-RSA-AES128-GCM-SHA256",
        // rfc_name
        "TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256",
        // encryption
        "AES_128_GCM",
        // key_exchange_verbose. kx = ECDH_RSA, au = ECDH
        "ECDH_RSA",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
    {
        // openssl_name
        "ECDH-RSA-AES256-GCM-SHA384",
        // rfc_name
        "TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384",
        // encryption
        "AES_256_GCM",
        // key_exchange_verbose. kx = ECDH_RSA, au = ECDH
        "ECDH_RSA",
        // forward secret
        false,
        // message authentication
        "AEAD",
    },
};

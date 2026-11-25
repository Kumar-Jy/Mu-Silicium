/** @file
  UEFI 2.12 BaseCryptLib compatibility APIs for the runtime crypto library.

  Copyright (c) Microsoft Corporation
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "InternalCryptLib.h"

#include <openssl/evp.h>
#include <openssl/pkcs7.h>
#include <openssl/x509.h>

/**
  Determine whether a DER-encoded X.509 certificate has a public key that
  can be used for signature verification by this crypto provider.

  @param[in]  Cert      Pointer to the DER-encoded X.509 certificate.
  @param[in]  CertSize  Size of Cert in bytes.

  @retval TRUE   The certificate is valid and has a supported public key.
  @retval FALSE  The certificate is invalid or its public key is unsupported.

**/
BOOLEAN
EFIAPI
X509IsPublicKeySupported (
  IN CONST UINT8  *Cert,
  IN UINTN        CertSize
  )
{
  BOOLEAN        Status;
  CONST UINT8    *Temp;
  X509           *X509Cert;
  EVP_PKEY       *Pkey;
  INT32          KeyType;

  if ((Cert == NULL) || (CertSize == 0) || (CertSize > INT_MAX)) {
    return FALSE;
  }

  Status   = FALSE;
  X509Cert = NULL;
  Pkey     = NULL;

  Temp     = Cert;
  X509Cert = d2i_X509 (NULL, &Temp, (long)CertSize);
  if (X509Cert == NULL) {
    goto _Exit;
  }

  Pkey = X509_get_pubkey (X509Cert);
  if (Pkey == NULL) {
    goto _Exit;
  }

  KeyType = EVP_PKEY_id (Pkey);
  if ((KeyType == EVP_PKEY_RSA) ||
      (KeyType == EVP_PKEY_RSA_PSS) ||
      (KeyType == EVP_PKEY_EC))
  {
    Status = TRUE;
  }

_Exit:
  if (Pkey != NULL) {
    EVP_PKEY_free (Pkey);
  }

  if (X509Cert != NULL) {
    X509_free (X509Cert);
  }

  return Status;
}

/**
  Get the number of SignerInfo structures in a PKCS#7/CMS SignedData message.

  @param[in]  P7Data    Pointer to the PKCS#7/CMS message.
  @param[in]  P7Length  Length of the PKCS#7/CMS message in bytes.

  @retval >0  Number of SignerInfo structures.
  @retval 0   The input is invalid or contains no SignerInfo.

**/
UINTN
EFIAPI
CmsGetSignerInfoNum (
  IN  CONST UINT8  *P7Data,
  IN  UINTN        P7Length
  )
{
  UINTN                       SignerCount;
  BOOLEAN                     Wrapped;
  UINT8                       *SignedData;
  CONST UINT8                 *Temp;
  UINTN                       SignedDataSize;
  PKCS7                       *Pkcs7;
  STACK_OF (PKCS7_SIGNER_INFO) *SignerInfos;

  if ((P7Data == NULL) || (P7Length < 19) || (P7Length > INT_MAX)) {
    return 0;
  }

  SignerCount   = 0;
  Pkcs7         = NULL;
  SignerInfos   = NULL;

  if (!WrapPkcs7Data (P7Data, P7Length, &Wrapped, &SignedData, &SignedDataSize)) {
    return 0;
  }

  if (SignedDataSize > INT_MAX) {
    goto _Exit;
  }

  Temp  = SignedData;
  Pkcs7 = d2i_PKCS7 (NULL, (const unsigned char **)&Temp, (int)SignedDataSize);
  if ((Pkcs7 == NULL) || !PKCS7_type_is_signed (Pkcs7)) {
    goto _Exit;
  }

  SignerInfos = PKCS7_get_signer_info (Pkcs7);
  if (SignerInfos == NULL) {
    goto _Exit;
  }

  SignerCount = (UINTN)sk_PKCS7_SIGNER_INFO_num (SignerInfos);

_Exit:
  if (Pkcs7 != NULL) {
    PKCS7_free (Pkcs7);
  }

  if (!Wrapped) {
    OPENSSL_free (SignedData);
  }

  return SignerCount;
}

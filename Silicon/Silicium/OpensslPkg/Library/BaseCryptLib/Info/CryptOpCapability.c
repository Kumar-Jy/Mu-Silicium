/** @file
  Null crypto-operation capability reporting for the runtime crypto library.

  Copyright (C) Microsoft Corporation
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseCryptLib.h>

/**
  Reports that this library instance implements no crypto operations.

  @param[in]  OpIdGuid         GUID identifying the crypto operation.
  @param[out] Capabilities     Receives NULL.
  @param[out] CapabilityCount  Receives zero.

  @retval EFI_NOT_FOUND          No operation is implemented by this instance.
  @retval EFI_INVALID_PARAMETER  Any argument is NULL.
**/
EFI_STATUS
EFIAPI
GetCryptoOpCapability (
  IN  CONST EFI_GUID            *OpIdGuid,
  OUT BASE_CRYPT_OP_CAPABILITY  **Capabilities,
  OUT UINTN                     *CapabilityCount
  )
{
  if (Capabilities != NULL) {
    *Capabilities = NULL;
  }

  if (CapabilityCount != NULL) {
    *CapabilityCount = 0;
  }

  if ((OpIdGuid == NULL) || (Capabilities == NULL) || (CapabilityCount == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  return EFI_NOT_FOUND;
}

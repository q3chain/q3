// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2014-2016 The q3chain Core developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// q3chain code distributed under the GPLv3 license, see COPYING file.

#ifndef q3chain_q3chainCONSENSUS_H
#define q3chain_q3chainCONSENSUS_H

#if defined(BUILD_q3chain_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/q3chain-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBq3chainCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define q3chainCONSENSUS_API_VER 0

typedef enum q3chainconsensus_error_t
{
    q3chainconsensus_ERR_OK = 0,
    q3chainconsensus_ERR_TX_INDEX,
    q3chainconsensus_ERR_TX_SIZE_MISMATCH,
    q3chainconsensus_ERR_TX_DESERIALIZE,
} q3chainconsensus_error;

/** Script verification flags */
enum
{
    q3chainconsensus_SCRIPT_FLAGS_VERIFY_NONE      = 0,
    q3chainconsensus_SCRIPT_FLAGS_VERIFY_P2SH      = (1U << 0), // evaluate P2SH (BIP16) subscripts
    q3chainconsensus_SCRIPT_FLAGS_VERIFY_DERSIG    = (1U << 2), // enforce strict DER (BIP66) compliance
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not NULL, err will contain an error/success code for the operation
EXPORT_SYMBOL int q3chainconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, q3chainconsensus_error* err);

EXPORT_SYMBOL unsigned int q3chainconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // q3chain_q3chainCONSENSUS_H

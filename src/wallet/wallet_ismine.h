// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2014-2016 The q3chain Core developers
// Original code was distributed under the MIT software license.
// Copyright (c) 2014-2019 Coin Sciences Ltd
// q3chain code distributed under the GPLv3 license, see COPYING file.

#ifndef q3chain_WALLET_ISMINE_H
#define q3chain_WALLET_ISMINE_H

#include "keys/key.h"
#include "script/standard.h"

class CKeyStore;
class CScript;

/** IsMine() return codes */
enum isminetype
{
    ISMINE_NO = 0,
    ISMINE_WATCH_ONLY = 1,
    ISMINE_SPENDABLE = 2,
    ISMINE_ALL = ISMINE_WATCH_ONLY | ISMINE_SPENDABLE
};
/** used for bitflags of isminetype */
typedef uint8_t isminefilter;

isminetype IsMine(const CKeyStore& keystore, const CScript& scriptPubKey);
isminetype IsMine(const CKeyStore& keystore, const CTxDestination& dest);

isminetype IsMineKeyID(const CKeyStore& keystore, const CKeyID& dest);
isminetype IsMineScriptID(const CKeyStore& keystore, const CScriptID& dest);

#endif // q3chain_WALLET_ISMINE_H

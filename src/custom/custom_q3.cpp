// Copyright (c) 2014-2019 Coin Sciences Ltd
// q3chain code distributed under the GPLv3 license, see COPYING file.

#include "q3chain/q3chain.h"

void* custom_get_blockchain_default(const char *param,int* size,void *param_in)
{
    *size=0;
    
    return NULL;
}


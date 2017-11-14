/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __API_STORAGE_H
#define __API_STORAGE_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include "RpcApiInterface.h"

//////////////////////////////////////////////////////////////////////////

class ApiStorage : public ApiStorageInterface
{
public:
    ApiStorage(const StorageParameters& params);
    ~ApiStorage();

    void Parse();

private:
    StorageParameters m_params;
};

//////////////////////////////////////////////////////////////////////////
#endif // __API_STORAGE_H


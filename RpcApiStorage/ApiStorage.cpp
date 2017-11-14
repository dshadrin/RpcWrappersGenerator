/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#include "RpcApiStorage.h"
#include "ApiStorage.h"
#include "StorageException.h"

//////////////////////////////////////////////////////////////////////////
ApiStoragePtr ApiStorageInterface::Create(const StorageParameters& params)
{
    std::unique_ptr<ApiStorage> aPtr(new ApiStorage(params));
    if (!aPtr)
    {
        STG_EXCEPTION_ERROR("Cannot create ApiStorage instance");
    }
    
    aPtr->Parse();
    return ApiStoragePtr(aPtr.release());
}

//////////////////////////////////////////////////////////////////////////
ApiStorage::ApiStorage(const StorageParameters& params)
    : m_params(params)
{
}

//////////////////////////////////////////////////////////////////////////
ApiStorage::~ApiStorage()
{
}

//////////////////////////////////////////////////////////////////////////
void ApiStorage::Parse()
{

}

/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#include "StdInc.h"
#include "ApiStorage.h"
#include <boost/stacktrace.hpp>

//////////////////////////////////////////////////////////////////////////
void RPCAPI GeneratorPrintStackTrace(std::ostream& stream)
{
    stream << boost::stacktrace::stacktrace() << std::endl;
}

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

/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __RPC_API_INTERFACE_H
#define __RPC_API_INTERFACE_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#if defined(WIN32) && defined (SHARED_MODE)
#ifdef RPCAPISTORAGE_EXPORTS
#define RPCAPI __declspec(dllexport)
#else
#define RPCAPI __declspec(dllimport)
#endif
#else
#define RPCAPI
#endif

//////////////////////////////////////////////////////////////////////////
struct StorageParameters
{
    std::string apiXmlName;
};

class RPCAPI ApiStorageInterface;
typedef std::unique_ptr<ApiStorageInterface> ApiStoragePtr;

class RPCAPI ApiStorageInterface
{
public:
    ApiStorageInterface() = default;
    virtual ~ApiStorageInterface() = default;

    static ApiStoragePtr Create(const StorageParameters& params);
};

//////////////////////////////////////////////////////////////////////////
#endif // __RPC_API_INTERFACE_H

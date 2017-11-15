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

#include "StorageException.h"

//////////////////////////////////////////////////////////////////////////
// Types definitions and defines
//////////////////////////////////////////////////////////////////////////
typedef uint32_t ENTITY_ID_T;

#ifndef pure
#define pure =0
#endif

enum EItemTag : uint8_t
{
    enNone,
    enArgument,
    enArrayType,
    enCvQualifiedType,
    enEllipsis,
    enEnumValue,
    enEnumeration,
    enField,
    enFile,
    enFunction,
    enFunctionType,
    enFundamentalType,
    enGCC_XML,
    enNamespace,
    enPointerType,
    enStruct,
    enTypedef,
    enUnion,
    enVariable
};

//////////////////////////////////////////////////////////////////////////
// set of parameters for storage initialization
//////////////////////////////////////////////////////////////////////////
struct StorageParameters
{
    std::string apiXmlName;
};

//////////////////////////////////////////////////////////////////////////
class RPCAPI ApiStorageInterface;
typedef std::unique_ptr<ApiStorageInterface> ApiStoragePtr;

//////////////////////////////////////////////////////////////////////////
// interface to API storage
//////////////////////////////////////////////////////////////////////////
class RPCAPI ApiStorageInterface
{
public:
    ApiStorageInterface() = default;
    virtual ~ApiStorageInterface() = default;

    static ApiStoragePtr Create(const StorageParameters& params);
};

//////////////////////////////////////////////////////////////////////////
// interface to API items
//////////////////////////////////////////////////////////////////////////
struct RPCAPI ApiItem
{
    virtual ~ApiItem() = default;
    virtual ENTITY_ID_T GetID() const pure;
    virtual EItemTag GetTag() const pure;
};

//////////////////////////////////////////////////////////////////////////
#endif // __RPC_API_INTERFACE_H

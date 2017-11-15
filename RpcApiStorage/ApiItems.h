/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __API_ITEMS_H
#define __API_ITEMS_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include "RpcApiInterface.h"

//////////////////////////////////////////////////////////////////////////

class ApiItemBase : public ApiItem
{
public:
    ApiItemBase(EItemTag itemTag, ENTITY_ID_T itemId) : id(itemId), tag(itemTag) {}
    virtual ~ApiItemBase() = default;

    virtual ENTITY_ID_T GetID() const { return id; }
    virtual EItemTag GetTag() const { return tag; }

public:
    ENTITY_ID_T id;
    EItemTag tag;
};

//////////////////////////////////////////////////////////////////////////
#endif // __API_ITEMS_H


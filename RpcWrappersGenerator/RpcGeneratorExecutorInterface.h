/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __RPC_GENERATOR_INTERFACE_H
#define __RPC_GENERATOR_INTERFACE_H
#pragma once

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

class RpcGeneratorExecutorInterface;

typedef std::unique_ptr<RpcGeneratorExecutorInterface> RpcGeneratorExecutorPtr;

//////////////////////////////////////////////////////////////////////////

class RpcGeneratorExecutorInterface
{
public:
    RpcGeneratorExecutorInterface() = default;
    virtual ~RpcGeneratorExecutorInterface() = default;

    virtual void Execute(const std::string& cfgXmlName) = 0;
    static RpcGeneratorExecutorPtr Create();
};

//////////////////////////////////////////////////////////////////////////
#endif // __RPC_GENERATOR_INTERFACE_H

/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __RPC_GENERATOR_EXECUTOR_H
#define __RPC_GENERATOR_EXECUTOR_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include "RpcGeneratorExecutorInterface.h"
#include "RpcGeneratorConfigurator.h"
#include "RpcApiInterface.h"

//////////////////////////////////////////////////////////////////////////

class RpcGeneratorExecutor : public RpcGeneratorExecutorInterface
{
public:
    RpcGeneratorExecutor();
    virtual ~RpcGeneratorExecutor();

    virtual void Execute(const std::string& cfgXmlName) override;

private:
    RpcGeneratorConfiguratorPtr m_config;
    ApiStoragePtr m_storage;
};

//////////////////////////////////////////////////////////////////////////
#endif // __RPC_GENERATOR_EXECUTOR_H


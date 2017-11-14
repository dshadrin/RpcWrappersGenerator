/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

//////////////////////////////////////////////////////////////////////////

#include "RpcWrappersGenerator.h"
#include "RpcGeneratorExecutor.h"

//////////////////////////////////////////////////////////////////////////
RpcGeneratorExecutorPtr RpcGeneratorExecutorInterface::Create()
{
    RpcGeneratorExecutorPtr gPtr(new RpcGeneratorExecutor);
    return gPtr;
}

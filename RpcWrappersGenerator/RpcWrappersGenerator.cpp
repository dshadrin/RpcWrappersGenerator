/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

//////////////////////////////////////////////////////////////////////////

#include "RpcWrappersGenerator.h"
#include "RpcGeneratorExecutorInterface.h"

//////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    int retCode = -1;

    if (argc > 1)
    {
        if (std::string(argv[1]) == "generator-config.xml")
        {
            RpcGeneratorExecutorPtr gen = RpcGeneratorExecutorInterface::Create();
            gen->Execute(argv[1]);
        }
    }
    else
    {
        std::cout << "Empty command line" << std::endl;
    }

    return 0;
}


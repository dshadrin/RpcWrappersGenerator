/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

//////////////////////////////////////////////////////////////////////////

#include "RpcWrappersGenerator.h"
#include "RpcGeneratorExecutorInterface.h"

//////////////////////////////////////////////////////////////////////////

#define VERSION_STR "RPC wrappers generator [Version 0.10.1]\n" \
                    "Copyright (C) 2014-2017 Rhonda Software. All rights reserved.\n\n"

//////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
    std::cout << VERSION_STR;

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


/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

//////////////////////////////////////////////////////////////////////////

#include "RpcWrappersGenerator.h"
#include "RpcGeneratorExecutorInterface.h"
#include "GeneratorOptions.h"
#include "RpcApiInterface.h"
#include <boost/program_options.hpp>

//////////////////////////////////////////////////////////////////////////

#define VERSION_STR "RPC wrappers generator [Version 0.10.1]\n" \
                    "Copyright (C) 2014-2017 Rhonda Software. All rights reserved.\n\n"

//////////////////////////////////////////////////////////////////////////

int main(int argc, const char** argv)
{
    std::cout << VERSION_STR;
    GOptions so;
    int retCode = -1;

    try
    {
        switch (so.ParseOptions(argc, argv))
        {
        case GOptions::EGeneratorMode::help:
            so.PrintUsage();
            break;
        case GOptions::EGeneratorMode::generate:
            RpcGeneratorExecutorInterface::Create()->Execute(so.ConfigFileName());
            break;
        case GOptions::EGeneratorMode::configure:
        case GOptions::EGeneratorMode::complete:
        default:;
        }
        retCode = 0;
    }
    catch (StorageException& e)
    {
        PrintExeptionData(e);
    }
    catch (std::exception& e)
    {
        PrintExeptionData(e);
    }
    catch (...)
    {
        PrintExeptionData();
    }

    return retCode;
}

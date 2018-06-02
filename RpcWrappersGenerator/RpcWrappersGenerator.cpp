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
        case GOptions::eHelp:
            so.PrintUsage();
            break;
        case GOptions::eGenerate:
            RpcGeneratorExecutorInterface::Create()->Execute(so.ConfigFileName());
            break;
        case GOptions::eConfigure:
        case GOptions::eComplete:
        default:;
        }
        retCode = 0;
    }
    catch (StorageException& e)
    {
        // all get exception in this point are errors
        std::cerr << "ERROR: " << e.what();
        if (e.File() != nullptr)
        {
            std::cerr << " | " << e.File() << ":" << e.Line();
        }
        std::cerr << std::endl << std::endl;
        GeneratorPrintStackTrace(std::cerr);
    }
    catch (std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        GeneratorPrintStackTrace(std::cerr);
    }
    catch (...)
    {
        std::cerr << "ERROR: Unknown!" << std::endl << std::endl;
        GeneratorPrintStackTrace(std::cerr);
    }


    return retCode;
}

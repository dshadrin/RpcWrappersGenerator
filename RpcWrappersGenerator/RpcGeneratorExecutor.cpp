/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

//////////////////////////////////////////////////////////////////////////

#include "RpcWrappersGenerator.h"
#include "RpcGeneratorExecutor.h"
#include "RpcApiInterface.h"

//////////////////////////////////////////////////////////////////////////
RpcGeneratorExecutor::RpcGeneratorExecutor()
{
}

//////////////////////////////////////////////////////////////////////////
RpcGeneratorExecutor::~RpcGeneratorExecutor()
{
}

//////////////////////////////////////////////////////////////////////////
void RpcGeneratorExecutor::Execute(const std::string& cfgXmlName)
{
    try
    {
        if (!m_config)
        {
            if (!fs::exists(cfgXmlName))
            {
                STG_EXCEPTION_ERROR(GMSG << "Cannot find configuration: " << cfgXmlName);
            }

            m_config.reset(new RpcGeneratorConfigurator(cfgXmlName));

            if (!m_config)
            {
                STG_EXCEPTION_ERROR(GMSG << "Error create configuration: " << cfgXmlName);
            }
        }

        if (!m_storage)
        {
            StorageParameters params;
            params.apiXmlName = m_config->GetApiXmlName();

            if (!fs::exists(params.apiXmlName))
            {
                STG_EXCEPTION_ERROR(GMSG << "Cannot find API XML file: " << params.apiXmlName);
            }



            m_storage = ApiStorageInterface::Create(params);
        }
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
}

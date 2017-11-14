/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

//////////////////////////////////////////////////////////////////////////

#include "RpcWrappersGenerator.h"
#include "RpcGeneratorExecutor.h"
#include "GeneratorException.h"

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
                GEN_EXCEPTION_ERROR((MessageBuilder() << "Cannot find configuration: " << cfgXmlName).Str());
            }

            m_config.reset(new RpcGeneratorConfigurator(cfgXmlName));

            if (!m_config)
            {
                GEN_EXCEPTION_ERROR((MessageBuilder() << "Error create configuration: " << cfgXmlName).Str());
            }
        }

        if (!m_storage)
        {
            StorageParameters params;
            params.apiXmlName = m_config->GetApiXmlName();

            if (!fs::exists(params.apiXmlName))
            {
                GEN_EXCEPTION_ERROR((MessageBuilder() << "Cannot find API XML file: " << params.apiXmlName).Str());
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
        std::cerr << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "ERROR: Unknown!" << std::endl;
    }
}

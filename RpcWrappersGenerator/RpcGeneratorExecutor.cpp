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
        // init configuration
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

        // init API storage
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
}

/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

//////////////////////////////////////////////////////////////////////////

#include "RpcWrappersGenerator.h"
#include "RpcGeneratorConfigurator.h"
#include "GeneratorException.h"
#include <boost/property_tree/xml_parser.hpp>

//////////////////////////////////////////////////////////////////////////
const std::string API_XML_NAME_PATH = "IPCgen.Platform.ApiFile";

//////////////////////////////////////////////////////////////////////////
RpcGeneratorConfigurator::RpcGeneratorConfigurator(const std::string& cfgXmlName)
{
    boost::property_tree::xml_parser::read_xml(cfgXmlName, m_pt);
}

//////////////////////////////////////////////////////////////////////////
std::string RpcGeneratorConfigurator::GetApiXmlName() const
{
    std::string xmlName = m_pt.get<std::string>(API_XML_NAME_PATH, "");
    if (xmlName.empty())
    {
        GEN_EXCEPTION_ERROR((MessageBuilder() << "Wrong XML configuration format: " << API_XML_NAME_PATH << " is absent").Str());
    }
    return xmlName;
}

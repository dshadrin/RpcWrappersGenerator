/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __RPC_GENERATOR_CONFIGURATOR_H
#define __RPC_GENERATOR_CONFIGURATOR_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include <boost/property_tree/ptree.hpp>

//////////////////////////////////////////////////////////////////////////

using boost::property_tree::ptree;
class RpcGeneratorConfigurator;
typedef std::unique_ptr<RpcGeneratorConfigurator> RpcGeneratorConfiguratorPtr;

//////////////////////////////////////////////////////////////////////////

class RpcGeneratorConfigurator
{
public:
    RpcGeneratorConfigurator(const std::string& cfgXmlName);
    ~RpcGeneratorConfigurator() = default;

    std::string GetApiXmlName() const;

private:
    ptree m_pt;
};

//////////////////////////////////////////////////////////////////////////
#endif // __RPC_GENERATOR_CONFIGURATOR_H

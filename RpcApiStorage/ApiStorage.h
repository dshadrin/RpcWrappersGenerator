/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __API_STORAGE_H
#define __API_STORAGE_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include "ApiItems.h"

//////////////////////////////////////////////////////////////////////////

class ApiStorage : public ApiStorageInterface
{
public:
    ApiStorage(const StorageParameters& params);
    ~ApiStorage();

    // check if node with tag <tag> need to be added
    bool IsHandleTag(const std::string& tagName) const;
    // add data from XML node
    void AddNode(const std::string& tagName, const std::map<std::string, std::string>& attrMap);
    // parsing and store data
    void LoadXmlData();

private:
    EItemTag TagName2TagValue(const std::string& name);

private:
    StorageParameters m_params;

    static const std::vector<std::string> nodeNames;
};

//////////////////////////////////////////////////////////////////////////
#endif // __API_STORAGE_H


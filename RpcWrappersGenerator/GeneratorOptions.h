/*
* Copyright (C) 2018 Rhonda Software.
* All rights reserved.
*/

#ifndef __OPTIONS_GENERATOR_H
#define __OPTIONS_GENERATOR_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include "StdInc.h"

//////////////////////////////////////////////////////////////////////////

class GOptions
{
public:
    enum class EGeneratorMode { help, configure, generate, complete };

    explicit GOptions();

    void PrintUsage();
    EGeneratorMode ParseOptions(int ac, const char** av);

    const std::string& ConfigFileName() const { return configName; }

private:
    EGeneratorMode mode;
    fs::path outFolder;
    fs::path configTemplate;
    std::string configName;
    std::string apiCfile;
    std::string targets;
    std::vector<fs::path> iniList;
    std::string cc;
    bool absolutePaths;
};

//////////////////////////////////////////////////////////////////////////
#endif // __OPTIONS_GENERATOR_H

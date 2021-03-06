/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __RPC_WRAPPERS_GENERATOR_H
#define __RPC_WRAPPERS_GENERATOR_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#include <SDKDDKVer.h>
#endif // _MSC_VER

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <iostream>

#ifdef _MSC_VER                                                  
#include <filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#endif

//////////////////////////////////////////////////////////////////////////
#endif // __RPC_WRAPPERS_GENERATOR_H

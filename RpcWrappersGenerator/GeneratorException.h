/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __GENERATOR_EXCEPTION_H
#define __GENERATOR_EXCEPTION_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include "StorageException.h"

//////////////////////////////////////////////////////////////////////////

class GeneratorException : public StorageException
{
public:
    explicit GeneratorException( const std::string& what_arg, EErrorSeverity sev = ES_ERROR, const char * file = nullptr, int line = 0 )
        : StorageException(what_arg, sev, file, line) {}
    ~GeneratorException() = default;
};

#define GEN_EXCEPTION_ERROR(msg) throw GeneratorException(msg, ES_ERROR, __FILE__, __LINE__)
#define GEN_EXCEPTION_WARNING(msg) throw GeneratorException(msg, ES_WARNING, __FILE__, __LINE__)
#define GEN_EXCEPTION_LOGIC(msg) throw GeneratorException(msg, ES_LOGICAL)
#define GEN_EXCEPTION(msg, sev) throw GeneratorException(msg, sev, __FILE__, __LINE__)

//////////////////////////////////////////////////////////////////////////
#endif // __GENERATOR_EXCEPTION_H

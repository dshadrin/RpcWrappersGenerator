/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#ifndef __STORAGE_EXCEPTION_H
#define __STORAGE_EXCEPTION_H
#pragma once

//////////////////////////////////////////////////////////////////////////

#include <strstream>

//////////////////////////////////////////////////////////////////////////

enum EErrorSeverity
{
    ES_LOGICAL,     // no error
    ES_WARNING,     // continue execution (print warning and continue)
    ES_ERROR        // break execution (print error message and stop execution)     
};

//////////////////////////////////////////////////////////////////////////

class MessageBuilder
{
public:
    MessageBuilder() = default;
    ~MessageBuilder() = default;

    template<typename T>
    MessageBuilder& operator<<(const T& val)
    {
        oss << val;
        return *this;
    }

    std::string Str() const { return oss.str(); }

private:
    std::ostringstream oss;
};

//////////////////////////////////////////////////////////////////////////

class StorageException : public std::runtime_error
{
public:
    explicit StorageException(MessageBuilder& mb, EErrorSeverity sev = ES_ERROR, const char * file = nullptr, int line = 0)
        : std::runtime_error(mb.Str())
        , m_file(file)
        , m_line(line)
        , m_severity(sev) {}

    explicit StorageException( const std::string& what_arg, EErrorSeverity sev = ES_ERROR, const char * file = nullptr, int line = 0 )
        : std::runtime_error(what_arg)
        , m_file(file)
        , m_line(line)
        , m_severity(sev) {}

    ~StorageException() = default;

    const char * File() const { return m_file; }
    int Line() const { return m_line; }
    EErrorSeverity Severity() const { return m_severity; }

private:
    const char * m_file;
    int m_line;
    EErrorSeverity m_severity;
};

#define STG_EXCEPTION_ERROR(msg) throw StorageException(msg, ES_ERROR, __FILE__, __LINE__)
#define STG_EXCEPTION_WARNING(msg) throw StorageException(msg, ES_WARNING, __FILE__, __LINE__)
#define STG_EXCEPTION_LOGIC(msg) throw StorageException(msg, ES_LOGICAL)
#define STG_EXCEPTION(msg, sev) throw StorageException(msg, sev, __FILE__, __LINE__)

//////////////////////////////////////////////////////////////////////////
#endif // __STORAGE_EXCEPTION_H

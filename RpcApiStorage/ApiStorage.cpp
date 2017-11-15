/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

#include "StdInc.h"
#include "ApiStorage.h"
#include "SAXHandlers.h"
#include <boost/stacktrace.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>

//////////////////////////////////////////////////////////////////////////
// sorted array of used nodes
const std::vector<std::string> ApiStorage::nodeNames =
{
    "Argument",
    "ArrayType",
    "CvQualifiedType",
    "Ellipsis",
    "EnumValue",
    "Enumeration",
    "Field",
    "File",
    "Function",
    "FunctionType",
    "FundamentalType",
    "GCC_XML",
    "Namespace",
    "PointerType",
    "Struct",
    "Typedef",
    "Union",
    "Variable"
};

//////////////////////////////////////////////////////////////////////////
void RPCAPI GeneratorPrintStackTrace(std::ostream& stream)
{
    stream << boost::stacktrace::stacktrace() << std::endl;
}

//////////////////////////////////////////////////////////////////////////
ApiStoragePtr ApiStorageInterface::Create(const StorageParameters& params)
{
    std::unique_ptr<ApiStorage> aPtr(new ApiStorage(params));
    if (!aPtr)
    {
        STG_EXCEPTION_ERROR("Cannot create ApiStorage instance");
    }
    
    aPtr->LoadXmlData();
    return ApiStoragePtr(aPtr.release());
}

//////////////////////////////////////////////////////////////////////////
ApiStorage::ApiStorage(const StorageParameters& params)
    : m_params(params)
{
}

//////////////////////////////////////////////////////////////////////////
ApiStorage::~ApiStorage()
{
}

//////////////////////////////////////////////////////////////////////////
void ApiStorage::LoadXmlData()
{
    try
    {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch)
    {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::string errMsg = "Error during XERCEC-C initialization!: ";
        errMsg += message;
        XMLString::release(&message);
        STG_EXCEPTION_ERROR(errMsg);
    }

    try
    {
        std::unique_ptr<xercesc::SAXParser> parser(new SAXParser());
        std::unique_ptr<xercesc::DocumentHandler> docHandler(new SAXHandlers(*this));
        parser->setDocumentHandler(docHandler.get());
        parser->setErrorHandler(dynamic_cast<xercesc::ErrorHandler*>(docHandler.get()));

        parser->parse(m_params.apiXmlName.c_str());
    }
    catch (const XMLException& e)
    {
        char* message = XMLString::transcode(e.getMessage());
        std::string errMsg = "XMLException message is: ";
        errMsg += message;
        XMLString::release(&message);
        STG_EXCEPTION_ERROR(errMsg);
    }
    catch (const SAXParseException& e)
    {
        char* message = XMLString::transcode(e.getMessage());
        std::string errMsg = "SAXParseException message is: ";
        errMsg += message;
        XMLString::release(&message);
        STG_EXCEPTION_ERROR(errMsg);
    }
    catch (std::exception& e)
    {
        STG_EXCEPTION_ERROR(GMSG << "Exception message is: " << e.what());
    }
    catch (...)
    {
        STG_EXCEPTION_ERROR("Unexpected Exception");
    }
}

//////////////////////////////////////////////////////////////////////////
bool ApiStorage::IsHandleTag(const std::string& tagName) const
{
    return std::binary_search(std::begin(nodeNames), std::end(nodeNames), tagName);
}

//////////////////////////////////////////////////////////////////////////
EItemTag ApiStorage::TagName2TagValue(const std::string& tagName)
{
    EItemTag tag = EItemTag::enNone;
    auto it = std::lower_bound(std::begin(nodeNames), std::end(nodeNames), tagName);
    if (it != std::end(nodeNames))
    {
        tag = static_cast<EItemTag>(std::distance(std::begin(nodeNames), it) + 1);
    }
    return tag;
}

void ApiStorage::AddNode(const std::string& tagName, const std::map<std::string, std::string>& attrMap)
{
    EItemTag tag = TagName2TagValue(tagName);
    // TODO: implement
}

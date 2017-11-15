/*
 * Copyright (C) 2016 Rhonda Software.
 * All rights reserved.
 */

#ifndef __ETF_SAX_HANDLERS_H
#define __ETF_SAX_HANDLERS_H

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <stack>

class ApiStorage;

XERCES_CPP_NAMESPACE_USE

class SAXHandlers : public HandlerBase
{
public:
    // -----------------------------------------------------------------------
    //  Constructors
    // -----------------------------------------------------------------------
    SAXHandlers(ApiStorage& stg);
    ~SAXHandlers();


    // -----------------------------------------------------------------------
    //  Implementations of the SAX DocumentHandler interface
    // -----------------------------------------------------------------------
    void endDocument();
    void endElement(const XMLCh* const name);
    void characters(const XMLCh* const chars, const XMLSize_t length);
    void ignorableWhitespace(const XMLCh* const chars, const XMLSize_t length);
    void processingInstruction(const XMLCh* const target, const XMLCh* const data);
    void startDocument();
    void startElement(const XMLCh* const name, AttributeList& attributes);

    // -----------------------------------------------------------------------
    //  Implementations of the SAX ErrorHandler interface
    // -----------------------------------------------------------------------
    void warning(const SAXParseException& exc);
    void error(const SAXParseException& exc);
    void fatalError(const SAXParseException& exc);

    // -----------------------------------------------------------------------
    //  Implementation of the SAX DTDHandler interface
    // -----------------------------------------------------------------------
    void notationDecl(const XMLCh* const name, const XMLCh* const publicId, const XMLCh* const systemId);
    void unparsedEntityDecl(const XMLCh* const name, const XMLCh* const publicId, const XMLCh* const systemId, const XMLCh* const notationName);

private :
    ApiStorage& astg;
    std::stack<std::string> tree_way;
};

#endif // __ETF_SAX_HANDLERS_H

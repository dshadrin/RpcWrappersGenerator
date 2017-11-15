/*
 * Copyright (C) 2017 Rhonda Software.
 * All rights reserved.
 */

//////////////////////////////////////////////////////////////////////////

#include "StdInc.h"
#include "SAXHandlers.h"
#include "ApiStorage.h"
#include <iostream>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/sax/AttributeList.hpp>

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//  SAXPrintHandlers: Constructors and Destructor
//////////////////////////////////////////////////////////////////////////
SAXHandlers::SAXHandlers(ApiStorage& stg)
    : astg(stg)
{
}

//////////////////////////////////////////////////////////////////////////
SAXHandlers::~SAXHandlers()
{
}


//////////////////////////////////////////////////////////////////////////
//  SAXHandlers: Overrides of the SAX ErrorHandler interface
//////////////////////////////////////////////////////////////////////////
void SAXHandlers::error(const SAXParseException& e)
{
    STG_EXCEPTION_ERROR(GMSG << "\nError at file " << e.getSystemId() << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber() << "\n  Message: " << e.getMessage());
}

//////////////////////////////////////////////////////////////////////////
void SAXHandlers::fatalError(const SAXParseException& e)
{
    STG_EXCEPTION_ERROR(GMSG << "\nFatal Error at file " << e.getSystemId() << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber() << "\n  Message: " << e.getMessage());
}

//////////////////////////////////////////////////////////////////////////
void SAXHandlers::warning(const SAXParseException& e)
{
    STG_EXCEPTION_ERROR(GMSG << "\nWarning at file " << e.getSystemId() << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber() << "\n  Message: " << e.getMessage());
}

//////////////////////////////////////////////////////////////////////////
//  SAXHandlers: Overrides of the SAX DTDHandler interface
//////////////////////////////////////////////////////////////////////////
void SAXHandlers::unparsedEntityDecl(const     XMLCh* const /* name */,
                                     const     XMLCh* const /* publicId */,
                                     const     XMLCh* const /* systemId */,
                                     const     XMLCh* const /* notationName */)
{
    // Not used at this time
}


//////////////////////////////////////////////////////////////////////////
void SAXHandlers::notationDecl(const   XMLCh* const /* name */,
                               const   XMLCh* const /* publicId */,
                               const   XMLCh* const /* systemId */)
{
    // Not used at this time
}


//////////////////////////////////////////////////////////////////////////
//  SAXHandlers: Overrides of the SAX DocumentHandler interface
//////////////////////////////////////////////////////////////////////////
void SAXHandlers::characters(const     XMLCh* const    chars,
                             const     XMLSize_t       length)
{
    // Not used at this time
}


//////////////////////////////////////////////////////////////////////////
void SAXHandlers::endDocument()
{
    std::cout << "Finish parsing XML file." << std::endl;
}


//////////////////////////////////////////////////////////////////////////
void SAXHandlers::endElement(const XMLCh* const name)
{
    std::string tag_name = XMLString::transcode(name);
    if (tree_way.top() == tag_name)
        tree_way.pop();
}


//////////////////////////////////////////////////////////////////////////
void SAXHandlers::ignorableWhitespace(const   XMLCh* const chars,
                                       const   XMLSize_t    length)
{
}


//////////////////////////////////////////////////////////////////////////
void SAXHandlers::processingInstruction(const  XMLCh* const target,
                                        const  XMLCh* const data)
{
}


//////////////////////////////////////////////////////////////////////////
void SAXHandlers::startDocument()
{
    std::cout << "Start parsing XML file." << std::endl;
}


//////////////////////////////////////////////////////////////////////////
void SAXHandlers::startElement(const   XMLCh* const    name,
                                       AttributeList&  attributes)
{
    std::string tag_name = XMLString::transcode(name);

    if (!tree_way.empty() && !astg.IsHandleTag(tree_way.top()))
        return;

    tree_way.push(tag_name);

    if (astg.IsHandleTag(tag_name))
    {
        XMLSize_t attr_size = attributes.getLength();
        std::map<std::string, std::string> attr;
        for(XMLSize_t i = 0; i < attr_size; ++i)
        {
            attr.insert(std::make_pair(XMLString::transcode(attributes.getName(i)),
                                       XMLString::transcode(attributes.getValue(i))));
        }

        astg.AddNode(tag_name, attr);
    }
}

//////////////////////////////////////////////////////////////////////////

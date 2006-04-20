//<<<<<< INCLUDES                                                       >>>>>>

#include "FWCore/Services/interface/SiteLocalConfig.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/ActivityRegistry.h"

#include "SealBase/DebugAids.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMCharacterData.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/util/XMLString.hpp>

#include <fstream>

using namespace xercesc;


//<<<<<< PRIVATE DEFINES                                                >>>>>>
//<<<<<< PRIVATE CONSTANTS                                              >>>>>>
//<<<<<< PRIVATE TYPES                                                  >>>>>>
//<<<<<< PRIVATE VARIABLE DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC VARIABLE DEFINITIONS                                    >>>>>>
//<<<<<< CLASS STRUCTURE INITIALIZATION                                 >>>>>>
//<<<<<< PRIVATE FUNCTION DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC FUNCTION DEFINITIONS                                    >>>>>>
//<<<<<< MEMBER FUNCTION DEFINITIONS                                    >>>>>>

inline std::string _toString(const XMLCh *toTranscode)
{
    std::string tmp(XMLString::transcode(toTranscode));
    return tmp;
}
	
inline XMLCh*  _toDOMS( std::string temp )
{
    XMLCh* buff = XMLString::transcode(temp.c_str());    
    return  buff;
}

edm::service::SiteLocalConfig::SiteLocalConfig (const edm::ParameterSet &pset,
						const edm::ActivityRegistry &activityRegistry)
{
    std::string configURL = "/etc/site-local-config.xml";
    char * tmp = getenv ("CMS_PATH");
    
    if (tmp)
	configURL = tmp + configURL;
    
    this->parse (configURL);	    
}

const std::string
edm::service::SiteLocalConfig::dataCatalog (void) const
{
    return  m_dataCatalog;    
}

const std::string
edm::service::SiteLocalConfig::calibCatalog (void) const
{
    return  m_calibCatalog;    
}

edm::service::SiteLocalConfig::FrontierProxies::const_iterator
edm::service::SiteLocalConfig::frontierProxyBegin (void) const
{
    return m_frontierProxies.begin ();    
}

edm::service::SiteLocalConfig::FrontierProxies::const_iterator
edm::service::SiteLocalConfig::frontierProxyEnd (void) const
{
    return m_frontierProxies.end ();    
}



void
edm::service::SiteLocalConfig::parse (const std::string &url)
{
    XercesDOMParser* parser = new XercesDOMParser;     
    parser->setValidationScheme(XercesDOMParser::Val_Auto);
    parser->setDoNamespaces(false);
    parser->parse(url.c_str());	
    DOMDocument* doc = parser->getDocument();
    ASSERT (doc);
    
    // The Site Config has the following format
    // <site-local-config>
    // <site name="FNAL"/>
    //   <event-data>
    //     <catalog url="trivialcatalog_file:/x/y/z.xml"/>
    //   </event-data>
    //   <calib-data>
    //     <catalog url="trivialcatalog_file:/x/y/z.xml"/>
    //     <frontier-proxy url="http://localhost:3128"/>
    //   </calib-data>
    // </site-local-config>
    
    // FIXME: should probably use the parser for validating the XML.
    
    DOMNodeList *sites = doc->getElementsByTagName (_toDOMS ("site"));
    unsigned int numSites = sites->getLength ();
    for (unsigned int i=0;
	 i < numSites; 
	 i++)
    {	
	DOMElement *site = static_cast <DOMElement *> (sites->item (i));
	
	// Parsing of the event data section
	{
	    DOMNodeList * eventDataList 
		= site->getElementsByTagName (_toDOMS ("event-data"));
	    if (	eventDataList->getLength () != 1)
	    {
		throw std::exception ();
	    }
	    
	    DOMElement *eventData 
		= static_cast <DOMElement *> (eventDataList->item (0));
	    
	    DOMNodeList *catalogs 
		= eventData->getElementsByTagName (_toDOMS ("catalog"));
	    
	    if (catalogs->getLength () != 1)
	    {
		throw std::exception ();	    
	    }
	    DOMElement * catalog 
		= static_cast <DOMElement *> (catalogs->item (0));
	    
	    m_calibCatalog = _toString (catalog->getAttribute (_toDOMS ("url")));
	}
	
	// Parsing of the calib-data section
	{
	    DOMNodeList * calibDataList 
		= site->getElementsByTagName (_toDOMS ("calib-data"));
	    
	    if (calibDataList->getLength () != 1)
	    {
		throw std::exception ();
	    }
	    
	    DOMElement *calibData 
		= static_cast <DOMElement *> (calibDataList->item (0));
	    
	    DOMNodeList *catalogs = calibData->getElementsByTagName (_toDOMS ("catalog"));
	    
	    if (catalogs->getLength () != 1)
	    {
		throw std::exception ();	    
	    }
	    
	    DOMElement *catalog
		= static_cast <DOMElement *> (catalogs->item (0));
	    

	    m_calibCatalog = _toString (catalog->getAttribute (_toDOMS ("url")));
	    
	    DOMNodeList *proxies 
		= calibData->getElementsByTagName (_toDOMS ("frontier-proxy"));
	    for (unsigned int i = 0;
		 i < proxies->getLength ();
		 i++)
	    {
		DOMElement *proxy 
		    = static_cast <DOMElement *> (proxies->item (i));
		
		m_frontierProxies.push_back (_toString (proxy->getAttribute (_toDOMS ("url"))));		
	    }	    	    
	}
    }
}	
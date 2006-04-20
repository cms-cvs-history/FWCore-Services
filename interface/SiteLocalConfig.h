#ifndef FRAMEWORK_SITE_LOCAL_CONFIG_H
# define FRAMEWORK_SITE_LOCAL_CONFIG_H

//<<<<<< INCLUDES                                                       >>>>>>
# include <string>
# include <list>

//<<<<<< PUBLIC DEFINES                                                 >>>>>>
//<<<<<< PUBLIC CONSTANTS                                               >>>>>>
//<<<<<< PUBLIC TYPES                                                   >>>>>>
namespace edm 
{
    class ParameterSet;
    class ActivityRegistry;
}

//<<<<<< PUBLIC VARIABLES                                               >>>>>>
//<<<<<< PUBLIC FUNCTIONS                                               >>>>>>
//<<<<<< CLASS DECLARATIONS                                             >>>>>>

namespace edm 
{
    namespace service 
    {
	class SiteLocalConfig
	{
	public:
	    typedef std::list<std::string> FrontierProxies;	    
	    SiteLocalConfig (const ParameterSet & pset,
			     const ActivityRegistry &activityRegistry);
	    
	    const std::string dataCatalog (void) const;
	    const std::string calibCatalog (void) const;
	    FrontierProxies::const_iterator frontierProxyBegin (void) const;
	    FrontierProxies::const_iterator frontierProxyEnd (void) const;
	    
	    // implicit copy constructor
	    // implicit assignment operator
	    // implicit destructor
	private:
	    void parse (const std::string &url);
	    std::string m_url;	    
	    std::string m_dataCatalog;
	    std::string m_calibCatalog;
	    FrontierProxies	m_frontierProxies;	    
	};
    }
}
    
//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

#endif // FRAMEWORK_SITE_LOCAL_CONFIG_H
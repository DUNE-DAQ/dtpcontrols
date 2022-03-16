//DTP headers
#include "dtpcontrols/toolbox.hpp"
#include "dtpcontrols/DTPPodNode.hpp"

// C++ headers
#include <sstream>
#include <cstdlib>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace dunedaq {
  namespace dtpcontrols {

//-----------------------------------------------------------------------------
    std::string find_connection_file() {
      
      std::string p("");

      std::string connfile("dtp_connections.xml");
      std::string search_path =std::getenv("DTPCONTROLS_SHARE"); 
      std::istringstream paths(search_path);
      
      std::string path;
      for (std::string path; std::getline(paths, path, ':'); ) {
	for (auto const& entry : boost::filesystem::recursive_directory_iterator(path)) {
	  if (boost::ends_with(entry.path().string(), connfile)) {
	    return std::string("file://")+entry.path().string();
	  }
	  
	} 
	
      }
      
      return p;
      
    }
//-----------------------------------------------------------------------------

  }  // namespace dtpcontrols

} // namespace dunedaq


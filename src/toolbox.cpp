/**
 * @file toolbox.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

//DTP headers
#include "dtpcontrols/toolbox.hpp"
#include "dtpcontrols/DTPPodNode.hpp"

// C++ headers
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace dunedaq {
  namespace dtpcontrols {

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

//-----------------------------------------------------------------------------    
    std::vector<std::uint32_t> format_36b_to_32b
    (const std::vector<std::uint64_t>& pattern_36b) {
      std::vector<std::uint32_t> pattern_32b;
      for(auto & item : pattern_36b) {
	pattern_32b.push_back(item & 0x3ffff);
	pattern_32b.push_back((item>>18) & 0x3ffff);
      }
      return pattern_32b;
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------    
    std::vector<std::uint64_t> format_32b_to_36b
    (const uhal::ValVector<uint32_t>& pattern_32b) {
      std::vector<std::uint64_t> pattern_36b;
      for(auto item=pattern_32b.begin(); item!=pattern_32b.end(); item+2) {
	pattern_36b.push_back(((*(item+1)&0x3ffff)<<18)+(*item & 0x3ffff));
      }
      return pattern_36b;
    }
//-----------------------------------------------------------------------------
    
  }  // namespace dtpcontrols
} // namespace dunedaq


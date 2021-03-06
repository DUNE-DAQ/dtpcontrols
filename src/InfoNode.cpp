/**
 * @file InfoNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/InfoNode.hpp"
#include "dtpcontrols/DTPPodNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
  namespace dtpcontrols {

    UHAL_REGISTER_DERIVED_NODE(InfoNode)

//-----------------------------------------------------------------------------
    InfoNode::InfoNode(const uhal::Node& node)
    : uhal::Node(node)
    {}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    InfoNode::~InfoNode() {}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------    

    std::map<std::string, uint32_t> InfoNode::get_firmware_config_info() const {
      auto info_node = getNode<InfoNode>("info");
      auto l_config_names = info_node.getNode("config").getNodes();
      std::map<std::string, uint32_t> l_firmware_info;
      for (auto& l_name : l_config_names) {
	std::cout << l_name <<std::endl;
	auto temp = info_node.getNode("config."+l_name).read();
	getClient().dispatch();
	l_firmware_info.insert({l_name, temp});
      }
      return l_firmware_info;
    }
//-----------------------------------------------------------------------------
    
  } // namespace dtpcontrols
} // namespace dunedaq

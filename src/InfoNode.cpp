/**
 * @file InfoNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/InfoNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(InfoNode)

//-----------------------------------------------------------------------------
InfoNode::InfoNode(const uhal::Node &node) : uhal::Node(node) {}

//-----------------------------------------------------------------------------
InfoNode::~InfoNode() {}

//-----------------------------------------------------------------------------
std::map<std::string, uint32_t> InfoNode::get_firmware_config_info() const {
  auto l_config_names = this->getNode("config").getNodes();
  std::map<std::string, uint32_t> l_firmware_info;
  for (auto &l_name : l_config_names) {
    auto temp = this->getNode("config." + l_name).read();
    getClient().dispatch();
    l_firmware_info.insert({l_name, temp});
  }
  return l_firmware_info;
}

//-----------------------------------------------------------------------------
std::map<std::string, uint32_t> InfoNode::get_firmware_id_info() const {
  auto l_id_names = this->getNode("id").getNodes();
  std::map<std::string, uint32_t> l_id_info;
  for (auto &l_name : l_id_names) {
    auto temp = this->getNode("id." + l_name).read();
    getClient().dispatch();
    l_id_info.insert({l_name, temp});
  }
  return l_id_info;
}

} // namespace dtpcontrols
} // namespace dunedaq

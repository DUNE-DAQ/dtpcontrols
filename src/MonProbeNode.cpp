/**
 * @file MonProbeNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/MonProbeNode.hpp"

namespace dunedaq {
  namespace dtpcontrols {
    
    UHAL_REGISTER_DERIVED_NODE(MonProbeNode)
    
    MonProbeNode::MonProbeNode(const uhal::Node& node) : uhal::Node(node) {}
    
    MonProbeNode::~MonProbeNode(){}
    
    MonProbeNodeInfo MonProbeNode::get_info() const {

      const uhal::Node& node = getNode("mon");

      MonProbeNodeInfo info;
      
      info.ready = node.getNode("ready").read();
      info.valid = node.getNode("valid").read();
      info.user = node.getNode("user").read();
      info.last = node.getNode("last").read();
      info.last_err = node.getNode("last_err").read();
      info.pkt_ctr = node.getNode("pkt_ctr").read();
      info.axi_err = node.getNode("axi_err").read();

      getClient().dispatch();

      return info;

    }
    

} // namespace dtpcontrols
} // namespace dunedaq

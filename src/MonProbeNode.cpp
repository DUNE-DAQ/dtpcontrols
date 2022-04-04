/**
 * @file MonProbeNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/MonProbeNode.hpp"

#include "logging/Logging.hpp"

namespace dunedaq {
  namespace dtpcontrols {
    
    UHAL_REGISTER_DERIVED_NODE(MonProbeNode)
    
    MonProbeNode::MonProbeNode(const uhal::Node& node) : uhal::Node(node) {}
    
    MonProbeNode::~MonProbeNode(){}
    
    MonProbeNodeInfo MonProbeNode::get_info() const {

      TLOG_DEBUG(0) << "Getting monitor probe info";

      MonProbeNodeInfo info;
      
      info.ready = getNode("ready").read();
/*      info.valid = getNode("valid").read();
      info.user = getNode("user").read();
      info.last = getNode("last").read();
      info.last_err = getNode("last_err").read();
      info.pkt_ctr = getNode("pkt_ctr").read();
      info.axi_err = getNode("axi_err").read(); */

      getClient().dispatch();

      return info;

    }
    

} // namespace dtpcontrols
} // namespace dunedaq

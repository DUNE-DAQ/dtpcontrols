/**
 * @file StreamProcessorArrayNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/StreamProcessorArrayNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(StreamProcessorArrayNode)

StreamProcessorArrayNode::StreamProcessorArrayNode(const uhal::Node& node) : uhal::Node(node) {}

StreamProcessorArrayNode::~StreamProcessorArrayNode(){}

void StreamProcessorArrayNode::cap_counters(const bool dispatch) {
  getNode("csr.ctrl.cap_ctrs").write(0x1);
  if(dispatch) {getClient().dispatch();}
}

void StreamProcessorArrayNode::stream_select(const uint32_t pipe, const bool dispatch) {
  getNode("csr.ctrl.stream_sel").write(pipe);
  if(dispatch) {getClient().dispatch();}  
}

const StreamProcessorNode& StreamProcessorArrayNode::get_stream_proc_node(void) const {
  return getNode<StreamProcessorNode>("stream_proc");
}

} // namespace dtpcontrols
} // namespace dunedaq

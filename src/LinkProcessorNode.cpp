/**
 * @file linkProcessorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <map>
#include <string>

#include "dtpcontrols/LinkProcessorNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(LinkProcessorNode)

LinkProcessorNode::LinkProcessorNode(const uhal::Node& node) : uhal::Node(node), 
                                                               m_n_streams(4) {
}

LinkProcessorNode::~LinkProcessorNode() {}

const DataRouterNode& LinkProcessorNode::get_data_router_node() const {
  return getNode<DataRouterNode>("drtr");
}

const StreamProcessorArrayNode& LinkProcessorNode::get_stream_proc_array_node() const {
  return getNode<StreamProcessorArrayNode>("stream_procs");
}

const CentralRouterInterfaceNode& LinkProcessorNode::get_central_router_node(uint i) const {
  

    if (i < 4) {
    std::string name("cr-if");
    name += std::to_string(i);
    return getNode<CentralRouterInterfaceNode>(name);
    //return node.getNode<CentralRouterInterfaceNode>(name);
  } else {
    // replace with ERS exception
    throw std::out_of_range("Link id out of bounds");
  }
}

  //std::string name("cr-if0");
  //return getNode<CentralRouterInterfaceNode>(name.c_str());
//}

void LinkProcessorNode::setup_dr(bool enable) const {
  // enable data reception
  auto l_dr_node = get_data_router_node().get_data_reception_node();
  l_dr_node.enable(enable);

  // enable DPR passthrough
  // TODO : add other modes
  auto l_dpr_node = get_data_router_node().get_dpr_node();
  l_dpr_node.set_mux_in(0x1);
  l_dpr_node.set_mux_out(0x1);

  getClient().dispatch();
}

void LinkProcessorNode::drop_empty(bool drop) const {

  // setup stream processors
  auto l_strm_proc_arr_node = get_stream_proc_array_node();
  for (int s = 0; s != m_n_streams; ++s) {
    l_strm_proc_arr_node.stream_select(static_cast<uint32_t>(s), false);
    auto l_strm_proc_node = l_strm_proc_arr_node.get_stream_proc_node();
    l_strm_proc_node.drop_empty(drop);
  }

  getClient().dispatch();
}

void LinkProcessorNode::set_threshold(int stream, uint32_t threshold) const {
  uint32_t strm = static_cast<uint32_t>(stream);
  auto l_strm_proc_arr_node = get_stream_proc_array_node();
  l_strm_proc_arr_node.stream_select(strm, false);
  l_strm_proc_arr_node.get_stream_proc_node().set_threshold(threshold);
  getClient().dispatch();
}

uint32_t LinkProcessorNode::get_threshold(int stream) const {
  uint32_t strm = static_cast<uint32_t>(stream);
  auto l_strm_proc_arr_node = get_stream_proc_array_node();
  l_strm_proc_arr_node.stream_select(strm, false);
  return l_strm_proc_arr_node.get_stream_proc_node().get_threshold();
}

void LinkProcessorNode::set_channel_mask(int stream, uint32_t channel, uint32_t mask) const {
  uint32_t strm = static_cast<uint32_t>(stream);
  auto l_strm_proc_arr_node = get_stream_proc_array_node();
  l_strm_proc_arr_node.stream_select(strm, false);
  l_strm_proc_arr_node.get_stream_proc_node().set_channel_mask(channel, mask);
  getClient().dispatch();
}

uint32_t LinkProcessorNode::get_channel_mask(int stream, uint32_t channel) const {
  uint32_t strm = static_cast<uint32_t>(stream);
  auto l_strm_proc_arr_node = get_stream_proc_array_node();
  l_strm_proc_arr_node.stream_select(strm, false);
  return l_strm_proc_arr_node.get_stream_proc_node().get_channel_mask(channel);
  
}

void LinkProcessorNode::set_channel_mask_all(int stream, uint64_t mask) const {
  uint32_t strm = static_cast<uint32_t>(stream);
  auto l_strm_proc_arr_node = get_stream_proc_array_node();
  l_strm_proc_arr_node.stream_select(strm, false);
  l_strm_proc_arr_node.get_stream_proc_node().set_channel_mask_all(mask, false);
  getClient().dispatch();
}

uint64_t LinkProcessorNode::get_channel_mask_all(int stream) const {
  uint32_t strm = static_cast<uint32_t>(stream);
  auto l_strm_proc_arr_node = get_stream_proc_array_node();
  l_strm_proc_arr_node.stream_select(strm, false);
  return l_strm_proc_arr_node.get_stream_proc_node().get_channel_mask_all();
}

void LinkProcessorNode::capture_pedestal(int stream, bool enable) const {
  uint32_t strm = static_cast<uint32_t>(stream);
  auto l_strm_proc_arr_node = get_stream_proc_array_node();
  l_strm_proc_arr_node.stream_select(strm, false);
  l_strm_proc_arr_node.get_stream_proc_node().capture_pedestal(enable, false);
  getClient().dispatch();

}

}  // namespace dtpcontrols
}  // namespace dunedaq

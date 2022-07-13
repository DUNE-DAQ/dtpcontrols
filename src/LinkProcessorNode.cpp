/**
 * @file linkProcessorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/LinkProcessorNode.hpp"

namespace dunedaq {
  namespace dtpcontrols {

    UHAL_REGISTER_DERIVED_NODE(LinkProcessorNode)

    LinkProcessorNode::LinkProcessorNode(const uhal::Node& node) : 
    uhal::Node(node),
      m_n_streams(4)
    {
    }

    LinkProcessorNode::~LinkProcessorNode() {}

    const DataRouterNode& LinkProcessorNode::get_data_router_node() const {
      return getNode<DataRouterNode>("drtr"); 
    }

    const StreamProcessorArrayNode& LinkProcessorNode::get_stream_proc_array_node() const {
      return getNode<StreamProcessorArrayNode>("stream_procs"); 
    }

    void LinkProcessorNode::setup(bool enable, bool drop_empty) const {

      // enable data reception
      if (enable) {
	auto l_dr_node = get_data_router_node().get_data_reception_node();
	l_dr_node.enable(false);
      }

      // enable DPR passthrough
      // TODO : add other modes
      auto l_dpr_node = get_data_router_node().get_dpr_node();
      l_dpr_node.set_mux_in(0x1);
      l_dpr_node.set_mux_out(0x1);

      // setup stream processors
      auto l_strm_proc_arr_node = get_stream_proc_array_node();
      for (uint32_t s=0; s!=m_n_streams; ++s) {
	l_strm_proc_arr_node.stream_select(s, false);
	auto l_strm_proc_node = l_strm_proc_arr_node.get_stream_proc_node();
	if (drop_empty) {
	  l_strm_proc_node.drop_empty(false);
	}
      }
    
      getClient().dispatch();

    }

    void LinkProcessorNode::set_threshold(uint32_t stream, uint32_t threshold) const {
      auto l_strm_proc_arr_node = get_stream_proc_array_node();    
      l_strm_proc_arr_node.stream_select(stream, false);
      l_strm_proc_arr_node.get_stream_proc_node().set_threshold(threshold);
      getClient().dispatch();
      
    }

    uint32_t LinkProcessorNode::get_threshold(uint32_t stream) const {

      auto l_strm_proc_arr_node = get_stream_proc_array_node();
      l_strm_proc_arr_node.stream_select(stream, false);
      return l_strm_proc_arr_node.get_stream_proc_node().get_threshold();

    }

    void LinkProcessorNode::set_channel_mask(uint32_t stream, uint32_t channel, uint32_t mask) const {
      
      auto l_strm_proc_arr_node = get_stream_proc_array_node();
      l_strm_proc_arr_node.stream_select(stream, false);
      l_strm_proc_arr_node.get_stream_proc_node().set_channel_mask(channel, mask);
      getClient().dispatch();
      
    }
    
    uint32_t LinkProcessorNode::get_channel_mask(uint32_t stream, uint32_t channel) const {
      
      auto l_strm_proc_arr_node = get_stream_proc_array_node();
      l_strm_proc_arr_node.stream_select(stream, false);
      return l_strm_proc_arr_node.get_stream_proc_node().get_channel_mask(channel);

    }
    void LinkProcessorNode::set_channel_mask_all(uint32_t stream, uint64_t mask) const {
      
      auto l_strm_proc_arr_node = get_stream_proc_array_node();
      l_strm_proc_arr_node.stream_select(stream, false);
      l_strm_proc_arr_node.get_stream_proc_node().set_channel_mask_all(mask, false);
      getClient().dispatch();
      
    }

    uint64_t LinkProcessorNode::get_channel_mask_all(uint32_t stream) const {

      auto l_strm_proc_arr_node = get_stream_proc_array_node();
      l_strm_proc_arr_node.stream_select(stream, false);
      return l_strm_proc_arr_node.get_stream_proc_node().get_channel_mask_all();

    }


  } // namespace dtpcontrols
} // namespace dunedaq


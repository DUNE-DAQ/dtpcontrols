/**
 * @file FlowMasterNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/FlowMasterNode.hpp"

#include <map>

namespace dunedaq {
  namespace dtpcontrols {

    UHAL_REGISTER_DERIVED_NODE(FlowMasterNode)

    FlowMasterNode::FlowMasterNode(const uhal::Node& node) : uhal::Node(node) {}
  
    FlowMasterNode::~FlowMasterNode() {}

    void FlowMasterNode::select_source_gbt(bool dispatch) const {
      getNode("csr.ctrl.gbt_src").write(0x0);
      if(dispatch) { getClient().dispatch(); }
    }

    void FlowMasterNode::select_source_wtor(bool dispatch) const {
      getNode("csr.ctrl.gbt_src").write(0x1);
      if(dispatch) { getClient().dispatch(); }
    }
  
    void FlowMasterNode::source_select(const std::string& source, const bool dispatch) {
      std::map<std::string, uint32_t> src_map{{"gbt", 0}, {"wibtor", 1}};
      if (source_sink_exists(source, src_map)) {
	getNode("csr.ctrl.gbt_src").write(src_map[source]);
	if(dispatch) {getClient().dispatch();}
      }
    }
  
    void FlowMasterNode::source_select(const uint32_t &source, const bool dispatch) {
      const std::vector<uint32_t> src_num{0, 1};
      if (source_sink_exists(source, src_num)) {
	getNode("csr.ctrl.src").write(src_num[source]);
	if(dispatch) {getClient().dispatch();}
      }
    }

    void FlowMasterNode::sink_select(const std::string& sink, bool dispatch) {
      std::map<std::string, uint32_t> sink_src{{"hits", 0}, {"link0", 1},
					       {"link1", 1}, {"link2", 1},
					       {"link3", 1}, {"link4", 1}};
      std::map<std::string, uint32_t> sink_link{{"hits", 0}, {"link0", 0},
						{"link1", 1}, {"link2", 2},
						{"link3", 3}, {"link4", 4}};
      if (source_sink_exists(sink, sink_src)) {
	getNode("csr.ctrl.sink_src").write(sink_src[sink]);
	if(dispatch) {getClient().dispatch();}
      }
  
      if (source_sink_exists(sink, sink_link)) {
	getNode("csr.ctrl.sink_link").write(sink_link[sink]);
	if(dispatch) {getClient().dispatch();}
      }
    }
  
    void FlowMasterNode::sink_select(const uint32_t& sink, bool dispatch) {
      std::vector<uint32_t> sink_src{0, 1};
      std::vector<std::uint32_t> sink_link{0, 1, 2, 3, 4};
      if (source_sink_exists(sink, sink_src)) {
	getNode("csr.ctrl.sink_src").write(sink_src[sink]);
	if(dispatch) {getClient().dispatch();}
      }
  
      if (source_sink_exists(sink, sink_link)) {
	getNode("csr.ctrl.sink_link").write(sink_link[sink]);
	if(dispatch) {getClient().dispatch();}
      }
    }

  } // namespace dtpcontrols
} // namespace dunedaq

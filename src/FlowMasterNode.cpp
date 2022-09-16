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

    void FlowMasterNode::set_source_gbt(bool dispatch) const {
      getNode("csr.ctrl.gbt_src").write(0x0);
      if(dispatch) { getClient().dispatch(); }
    }

    void FlowMasterNode::set_source_wtor(bool dispatch) const {
      getNode("csr.ctrl.gbt_src").write(0x1);
      if(dispatch) { getClient().dispatch(); }
    }

    uint32_t FlowMasterNode::get_source() const {
      uhal::ValWord< uint32_t > tmp = getNode("csr.ctrl.gbt_src").read();
      getClient().dispatch();
      return tmp.value();
    }
  
    void FlowMasterNode::set_sink_hits(bool dispatch) const {
      getNode("csr.ctrl.sink_src").write(0x0);
      if(dispatch) { getClient().dispatch(); }
    }

    void FlowMasterNode::set_sink_link(uint32_t link, bool dispatch) const {
      getNode("csr.ctrl.sink_src").write(0x1);
      getNode("csr.ctrl.sink_link").write(link & 0x7);
      if(dispatch) { getClient().dispatch(); }
    }

    uint32_t FlowMasterNode::get_sink() const {
      uhal::ValWord<uint32_t> tmp = getNode("csr.ctrl.sink_src").read();
      getClient().dispatch();
      return tmp.value();
    }

    void FlowMasterNode::set_outflow(uint32_t enable, bool dispatch) const {
      getNode("csr.ctrl.out_sel").write(enable);
      if(dispatch) { getClient().dispatch(); }
    }

  } // namespace dtpcontrols
} // namespace dunedaq

/**
 * @file ControlNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/ControlNode.hpp"

namespace dunedaq {
  namespace dtpcontrols {
    
    UHAL_REGISTER_DERIVED_NODE(ControlNode)
    
    ControlNode::ControlNode(const uhal::Node& node) : uhal::Node(node) {}
    
    ControlNode::~ControlNode(){}
    
    void ControlNode::nuke(bool dispatch) {
      getNode("csr.ctrl.nuke").write(0x1);
      if(dispatch) {getClient().dispatch();}
    }
    
    void ControlNode::soft_reset(bool dispatch) {
      getNode("csr.ctrl.soft_rst").write(0x1);
      if(dispatch) {getClient().dispatch();}
    }
    
    void ControlNode::master_reset(bool dispatch) {
      getNode("csr.ctrl.mst_rst").write(0x1);
      if(dispatch) {getClient().dispatch();}
      getNode("csr.ctrl.mst_rst").write(0x0);
      if(dispatch) {getClient().dispatch();}  
    }
    
  } // namespace dtpcontrols
} // namespace dunedaq

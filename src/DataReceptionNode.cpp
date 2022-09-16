/**
 * @file DataReceptionNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DataReceptionNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

  UHAL_REGISTER_DERIVED_NODE(DataReceptionNode)

  DataReceptionNode::DataReceptionNode(const uhal::Node& node) : uhal::Node(node) {}
  
  DataReceptionNode::~DataReceptionNode(){}

  void DataReceptionNode::enable(bool enable, bool dispatch) const {
    getNode("csr.ctrl.en").write(enable);
    if (dispatch) { getClient().dispatch(); }
  }
  
  void DataReceptionNode::reset_input_word_counter(bool dispatch) const {
    getNode("csr.ctrl.rst_inctr").write(0x1);
    getNode("csr.ctrl.rst_inctr").write(0x0);
    if(dispatch) {getClient().dispatch();}  
  }

  void DataReceptionNode::reset_output_word_counter(bool dispatch) const {
    getNode("csr.ctrl.rst_outctr").write(0x1);
    getNode("csr.ctrl.rst_outctr").write(0x0);
    if(dispatch) {getClient().dispatch();}  
  }

  void DataReceptionNode::error_reset(bool dispatch) const {
    getNode("csr.ctrl.err_rst").write(0x1);
    getNode("csr.ctrl.err_rst").write(0x0);
    if(dispatch) {getClient().dispatch();}  
  }

  void DataReceptionNode::reset(bool dispatch) const {
    reset_input_word_counter(false);
    reset_output_word_counter(false);
    error_reset(false);
    
    if(dispatch) {getClient().dispatch();}
  }
  
} // namespace dtpcontrols
} // namespace dunedaq

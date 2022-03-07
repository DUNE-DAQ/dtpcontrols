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
  
void DataReceptionNode::enable_data_reception(bool dispatch) {
  getNode("csr.ctrl.en").write(0x1);
  if(dispatch) {getClient().dispatch();}
}

void DataReceptionNode::reset_input_word_counter(bool dispatch) {
  getNode("csr.ctrl.rst_inctr").write(0x1);
  if(dispatch) {getClient().dispatch();}  
}

void DataReceptionNode::reset_output_word_counter(bool dispatch) {
  getNode("csr.ctrl.rst_outctr").write(0x1);
  if(dispatch) {getClient().dispatch();}  
}

  void DataReceptionNode::error_reset(bool dispatch) {
  getNode("csr.ctrl.err_rst").write(0x1);
  if(dispatch) {getClient().dispatch();}  
}

uhal::ValWord<uint32_t> DataReceptionNode::dual_port_ram_write_flag(bool dispatch) {
  uhal::ValWord<uint32_t> lDPRWF;  
  lDPRWF = getNode("stat.dpr_wen").read();
  if(dispatch) {getClient().dispatch();}  
  return lDPRWF;
  }

uhal::ValWord<uint32_t> DataReceptionNode::stick_error_bit(bool dispatch) {
  uhal::ValWord<uint32_t> lSEB;  
  lSEB =  getNode("stat.err").read();
  if(dispatch) {getClient().dispatch();}  
  return lSEB;
}

uhal::ValWord<uint32_t> DataReceptionNode::back_pressure_bit(bool dispatch) {
  uhal::ValWord<uint32_t> lBPB;  
  lBPB = getNode("stat.bp").read();
  if(dispatch) {getClient().dispatch();}  
  return lBPB;
}

uhal::ValWord<uint32_t> DataReceptionNode::out_of_sync(bool dispatch) {
  uhal::ValWord<uint32_t> lOOS;  
  lOOS = getNode("stat.oos").read();
  if(dispatch) {getClient().dispatch();}  
  return lOOS;
}

uhal::ValWord<uint32_t> DataReceptionNode::rx_word_count(bool dispatch) {
  uhal::ValWord<uint32_t> lRXWC;  
  lRXWC = getNode("rcvd_wrd_cnt").read();
  if(dispatch) {getClient().dispatch();}  
  return lRXWC;
}

uhal::ValWord<uint32_t> DataReceptionNode::send_word_count(bool dispatch) {
  uhal::ValWord<uint32_t> lSWC;
  lSWC =  getNode("sent_wrd_cnt").read();
  if(dispatch) {getClient().dispatch();}  
  return lSWC;
}

uhal::ValWord<uint32_t> DataReceptionNode::sent_packet_count(bool dispatch) {
  uhal::ValWord<uint32_t> lSPC;
  lSPC = getNode("sent_pkt_cnt").read();
  if(dispatch) {getClient().dispatch();}  
  return lSPC;
}

} // namespace dtpcontrols
} // namespace dunedaq

/**
 * @file WibuloatorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/WibulatorNode.hpp"
#include "logging/Logging.hpp"

namespace dunedaq {
  namespace dtpcontrols {

    UHAL_REGISTER_DERIVED_NODE(WibulatorNode)

//-----------------------------------------------------------------------------
    WibulatorNode::WibulatorNode(const uhal::Node& node) : uhal::Node(node) {}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    WibulatorNode::~WibulatorNode(){}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    void WibulatorNode::set_fire(bool dispatch) {
      getNode("csr.ctrl.fire").write(0x1);
      if(dispatch) {getClient().dispatch();}
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------    
    void WibulatorNode::set_max_word(const uint32_t& max_word, bool dispatch) {
      getNode("csr.ctrl.max_word").write(max_word);
      if(dispatch) {getClient().dispatch();}
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------    
    void WibulatorNode::set_buffer_address(bool dispatch) {
      getNode("buf.addr").write(0x0);
      if(dispatch) {getClient().dispatch();}
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------   
    void WibulatorNode::set_buffer_data(const std::vector<uint32_t> &values, bool dispatch) {
      getNode("buf.data").writeBlock(values);
      if(dispatch) {getClient().dispatch();}
    }
//-----------------------------------------------------------------------------    

//-----------------------------------------------------------------------------    
    void WibulatorNode::set_chain(uint32_t loop_value, bool dispatch) {
      getNode("csr.ctrl.chain").write(loop_value);
      if(dispatch) {getClient().dispatch();}
    }
//-----------------------------------------------------------------------------

    
//-----------------------------------------------------------------------------
    uhal::ValVector<uint32_t> WibulatorNode::get_buffer_data(const uint32_t& block_size, bool dispatch) {
      uhal::ValVector<uint32_t> buffer_data;
      buffer_data = getNode("buf.data").readBlock(block_size);
      if(dispatch) {getClient().dispatch();}
      return buffer_data;
    }
//-----------------------------------------------------------------------------    

//-----------------------------------------------------------------------------
    uhal::ValWord<uint32_t> WibulatorNode::get_address_width(const bool dispatch) {
      uhal::ValWord<uint32_t> addr_width{ getNode("csr.addr_width").read() };
      if(dispatch) {getClient().dispatch();}
      return addr_width;
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    uhal::ValWord<uint32_t> WibulatorNode::get_max_word(const bool dispatch) {
      uhal::ValWord<uint32_t> max_word{ getNode("csr.addr_width").read() };
      if(dispatch) {getClient().dispatch();}
      return max_word;
    }
//-----------------------------------------------------------------------------    

//-----------------------------------------------------------------------------
    uhal::ValWord<uint32_t> WibulatorNode::get_size(void) {
      uhal::ValWord<uint32_t> size { get_address_width(true) };
      return 1<<size;
    }
//-----------------------------------------------------------------------------
    
  } // namespace dtpcontrols
} // namespace dunedaq

/**
 * @file WibulatorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/WibulatorNode.hpp"
#include "dtpcontrols/toolbox.hpp"
#include "logging/Logging.hpp"
#include <cstdint>
#include <string>
#include <uhal/ValMem.hpp>

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
    void WibulatorNode::write_pattern(std::vector<std::uint64_t> pattern) const {
      uhal::ValWord<uint32_t> addr_width{ getNode("csr.addr_width").read() };
      getClient().dispatch();   
      uint32_t buffer_size{addr_width};
      buffer_size = 1<<buffer_size;
      if (pattern.size() > buffer_size) {pattern.resize(buffer_size);}
      TLOG() << "Writing Wibulator pattern of length " << pattern.size();
      std::vector<uint32_t> ported_pattern = format_36b_to_32b(pattern); 
      getNode("buf.addr").write(0x0);
      getNode("buf.data").writeBlock(ported_pattern);
      getNode("csr.ctrl.max_word").write(((pattern.size()-1)>0)?(pattern.size()-1):0);
      getClient().dispatch();
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    std::vector<std::uint64_t> WibulatorNode::read_pattern() const {
      uhal::ValWord<uint32_t> aw = getNode("csr.addr_width").read();
      uhal::ValWord<uint32_t> mw = getNode("csr.max_word").read();
      getClient().dispatch();
      uint32_t length = 1<<(aw+1);
      getNode("buf.addr").write(0x0);
      auto p = getNode("buf.data").readBlock(length);
      getClient().dispatch();
      return format_32b_to_36b(p);
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    void WibulatorNode::fire() const {
      set_fire(0, false);
      set_fire(1, true);
    }
//-----------------------------------------------------------------------------    
    
//-----------------------------------------------------------------------------
    void WibulatorNode::set_fire(const uint32_t& fire_value, bool dispatch) const {
      getNode("csr.ctrl.fire").write(fire_value);
      if(dispatch) {getClient().dispatch();}
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    uhal::ValWord<uint32_t> WibulatorNode::get_address_width(bool dispatch) const {
      uhal::ValWord<uint32_t> addr_width{ getNode("csr.addr_width").read() };
      if(dispatch) {getClient().dispatch();}
      return addr_width;
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    uhal::ValWord<uint32_t> WibulatorNode::get_size(void) const {
      uhal::ValWord<uint32_t> size { get_address_width(true) };
      return 1<<size.value();
    }
//-----------------------------------------------------------------------------
  } // namespace dtpcontrols
} // namespace dunedaq

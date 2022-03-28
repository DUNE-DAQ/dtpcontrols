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
    std::vector<std::uint64_t> WibulatorNode::load_WIB_pattern_from_file(const std::string& path) {
      const char separator =  ' ';
      std::ifstream pattern_file_stream(path);
      if (!pattern_file_stream.is_open()) {
	//ers place holder
      }
      // each pattern-file line is of example form '0x00554a00 1 0 0 1'
      else {
	std::vector<std::uint64_t> pattern_data;
	std::string pattern_line;
	while(std::getline(pattern_file_stream, pattern_line)) {
	  std::stringstream streamData(pattern_line);
	  std::string val;
	  std::vector<std::uint64_t> tokens{0, 0, 0, 0, 0};
	  uint32_t count = 0;
	  while (std::getline(streamData, val, separator)) {
	    tokens[count] = std::stoul(val);
	    count+=1;
	  }
	  pattern_data.push_back(tokens[0]+(tokens[1] << 32) + (tokens[2] << 33)
			 + (tokens[3] << 34) + (tokens[4] << 35));
	}
	return pattern_data;
      }
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    void WibulatorNode::write_pattern(std::vector<std::uint64_t> pattern) {
      auto buffer_size = get_size();
      pattern.erase(pattern.end()-buffer_size, pattern.end());
      uint64_t pattern_length = pattern.size();
      TLOG() << "Writing Wibulator pattern of length " << pattern_length;
      std::vector<uint32_t> ported_pattern = format_36b_to_32b(pattern); 
      getNode("buf.addr").write(0x0);
      getNode("buf.data").writeBlock(ported_pattern);
      getNode("csr.ctrl.max_word").write(((pattern_length-1)>0)?(pattern_length-1):0);
      getClient().dispatch();
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    std::vector<std::uint64_t> WibulatorNode::read_pattern() {
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
    void WibulatorNode::fire() {
      set_fire(0, false);
      set_fire(1, true);
    }
//-----------------------------------------------------------------------------    
    
//-----------------------------------------------------------------------------
    void WibulatorNode::set_fire(const uint32_t& fire_value, bool dispatch) {
      getNode("csr.ctrl.fire").write(fire_value);
      if(dispatch) {getClient().dispatch();}
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    uhal::ValWord<uint32_t> WibulatorNode::get_address_width(bool dispatch) {
      uhal::ValWord<uint32_t> addr_width{ getNode("csr.addr_width").read() };
      if(dispatch) {getClient().dispatch();}
      return addr_width;
    }
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
    uhal::ValWord<uint32_t> WibulatorNode::get_size(void) {
      uhal::ValWord<uint32_t> size { get_address_width(true) };
      return 1<<size.value();
    }
//-----------------------------------------------------------------------------
  } // namespace dtpcontrols
} // namespace dunedaq

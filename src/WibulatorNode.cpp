/**
 * @file WibulatorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/WibulatorNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(WibulatorNode)

//-----------------------------------------------------------------------------
WibulatorNode::WibulatorNode(const uhal::Node& node)
  : uhal::Node(node)
{}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
WibulatorNode::~WibulatorNode() {}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
  void WibulatorNode::set_fire(bool dispatch) {
    getNode("csr.ctrl.fire").write(0x1);
    if(dispatch) {getClient().dispatch();}
  }

  void WibulatorNode::set_max_word(const uint32_t& max_word, bool dispatch) {
    getNode("csr.ctrl.max_word").write(max_word);
    if(dispatch) {getClient().dispatch();}
  }

  void WibulatorNode::set_buffer_address(bool dispatch) {
    getNode("buf.addr").write(0x1);
    if(dispatch) {getClient().dispatch();}
  }

  void WibulatorNode::set_buffer_data(const std::vector<uint32_t> &values, const bool dispatch) {
    getNode("buf.data").writeBlock(values);
    if(dispatch) {getClient().dispatch();}
  }

  void WibulatorNode::set_chain(bool dispatch) {
    getNode("csr.ctrl.chain").write(0x1);
    if(dispatch) {getClient().dispatch();}
  }

  uhal::ValVector<uint32_t> WibulatorNode::get_buffer_data(const uint32_t& block_size, const bool) {
    uhal::ValVector<uint32_t> buffer_data;
    buffer_data = getNode("buf.data").readBlock(block_size);
    getClient().dispatch();
    return buffer_data;
  }


} // namespace dtpcontrols
} // namespace dunedaq

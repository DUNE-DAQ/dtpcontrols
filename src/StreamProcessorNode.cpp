/**
 * @file StreamProcessorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/StreamProcessorNode.hpp"
#include "dtpcontrols/MonProbeNode.hpp"

#include <algorithm>
#include <vector>

namespace dunedaq {
  namespace dtpcontrols {

    UHAL_REGISTER_DERIVED_NODE(StreamProcessorNode)

    StreamProcessorNode::StreamProcessorNode(const uhal::Node& node) : uhal::Node(node),
      m_n_mon_probes(6) {}

    StreamProcessorNode::~StreamProcessorNode(){}

    int StreamProcessorNode::get_n_probes() const {
      return m_n_mon_probes;
    }
    
    const MonProbeNode& StreamProcessorNode::get_mon_probe_node(uint32_t i) const {
      std::string name("csr.mon.p");
      name += std::to_string(i);
      return getNode<MonProbeNode>(name);
    }

    void StreamProcessorNode::drop_empty(bool dispatch) const {
      getNode("csr.ctrl.drop_empty").write(0x1);
      if(dispatch) {getClient().dispatch();}
    }

    void StreamProcessorNode::set_threshold(const uint32_t threshold, bool dispatch) const {

      if (threshold > 0 && threshold < 0x7fff){ // from hfButler; set in firmware JS thinks
	getNode("csr.hitfinder.threshold").write(threshold);
	if(dispatch) {getClient().dispatch();}
      }
      else {} //placeholder for ERS error
    }
    
    uint64_t StreamProcessorNode::get_channel_mask() const {
      
      const uint64_t& mask_00to31 = getNode("csr.mask.ch-00-31").read();
      const uint64_t& mask_32to63 = getNode("csr.mask.ch-32-63").read();

      getClient().dispatch();

      uint64_t mask = mask_00to31 + (mask_32to63 << 32);
      return mask;

    }

    void StreamProcessorNode::set_channel_mask(uint64_t mask, bool dispatch) const {

      getNode("csr.mask.ch-00-31").write( mask & 0xFFFFFFFF );
      getNode("csr.mask.ch-00-31").write( (mask >> 32) & 0xFFFFFFFF );
      if (dispatch) { getClient().dispatch(); }

    }

    void StreamProcessorNode::mask_channel(int channel) const {

      // get current mask
      uint64_t mask = get_channel_mask();

      // mask the channel required
      mask &= (0x1 << channel);
      set_channel_mask(mask, true);

      // never makes sense to do this and not dispatch ?
      getClient().dispatch();

    }

    void StreamProcessorNode::set_mask_channel_00to31(const uint32_t mask00to31,
						      bool dispatch,
						      bool mask_en_dsbl) const {
      if (mask_en_dsbl) {
	getNode("csr.mask.ch-00-31").write(mask00to31);
      }
      else {
	getNode("csr.mask.ch-00-31").write(~mask00to31);    
      }
      if(dispatch) {getClient().dispatch();}  
    }

    void StreamProcessorNode::set_mask_channel_32to63(const uint32_t mask32to63,
						      bool dispatch,
						      bool mask_en_dsbl) const {
      if (mask_en_dsbl){
	getNode("csr.mask.ch-00-31").write(mask32to63);    
      }
      else {
	getNode("csr.mask.ch-00-31").write(~mask32to63);    
      }
      if(dispatch) {getClient().dispatch();}
    }

    void StreamProcessorNode::set_mask_channels(const uint64_t msb00to31_lsb31to64,
						bool dispatch, bool mask_en_dsbl) const {
      if (mask_en_dsbl){
	set_mask_channel_32to63(msb00to31_lsb31to64, dispatch);
	set_mask_channel_00to31(msb00to31_lsb31to64 >> 32, dispatch);
      }
      else {
	set_mask_channel_32to63(~msb00to31_lsb31to64, dispatch);
	set_mask_channel_00to31(~msb00to31_lsb31to64 >> 32, dispatch);
      }
    }
    
    const uhal::ValWord<uint32_t> StreamProcessorNode::get_mask_channel_00to31(bool dispatch) const {
      uhal::ValWord<uint32_t> m00To32 = getNode("csr.mask.ch-00-31").read();
      if(dispatch) {getClient().dispatch();}
      return m00To32;
    }

    const uhal::ValWord<uint32_t> StreamProcessorNode::get_mask_channel_32to63(bool dispatch) const {
      uhal::ValWord<uint32_t> m32To63 = getNode("csr.mask.ch-32-63").read();
      if(dispatch) {getClient().dispatch();}
      return m32To63;
    }

  } // namespace dtpcontrols
} // namespace dunedaq

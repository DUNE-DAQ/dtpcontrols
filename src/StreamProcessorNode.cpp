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
      m_n_mon_probes(8) {
        // FIXME
        // m_n_mon_probes = getNodes("csr\\.mon").size();
      }

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

    uint32_t StreamProcessorNode::get_threshold() const {

      uhal::ValWord<uint32_t> tmp = getNode("csr.hitfinder.threshold").read();
      getClient().dispatch();
      return tmp.value();      

    }

    
    uint64_t StreamProcessorNode::get_channel_mask_all() const {
      
      const uint64_t& mask_00to31 = getNode("csr.mask.ch-00-31").read();
      const uint64_t& mask_32to63 = getNode("csr.mask.ch-32-63").read();

      getClient().dispatch();

      uint64_t mask = mask_00to31 + (mask_32to63 << 32);
      return mask;

    }

    void StreamProcessorNode::set_channel_mask_all(uint64_t mask, bool dispatch) const {
      getNode("csr.mask.ch-00-31").write( mask & 0xFFFFFFFF );
      getNode("csr.mask.ch-32-63").write( (mask >> 32) & 0xFFFFFFFF );
      if (dispatch) { getClient().dispatch(); }
    }

    uint32_t StreamProcessorNode::get_channel_mask(int channel) const {

      uint32_t mask = 0;
      
      if (channel >= 0 and channel <32) {
        mask = getNode("csr.mask.ch-00-31").read();
        mask &= (0x1 << channel);
        mask = (mask >> channel) & 0x1;
      }
      else if (channel >= 32 and channel <64) {
        mask = getNode("csr.mask.ch-32-63").read();
        mask &= (0x1 << channel);
        mask = (mask >> channel) & 0x1;
      }

      return mask;

    }

    void StreamProcessorNode::set_channel_mask(int channel, int mask) const {

      // get current mask
      uint64_t mask_all = get_channel_mask_all();

      // mask the channel required
      mask_all &= ((mask & 0x1) << channel);
      set_channel_mask_all(mask_all, true);

      // never makes sense to do this and not dispatch ?
      getClient().dispatch();

    }

    void StreamProcessorNode::capture_pedestal(bool enable, bool dispatch) const {
      getNode("csr.pedsub.pedsub_adj").write(enable);
      if (dispatch) { getClient().dispatch(); }
    }

  } // namespace dtpcontrols
} // namespace dunedaq

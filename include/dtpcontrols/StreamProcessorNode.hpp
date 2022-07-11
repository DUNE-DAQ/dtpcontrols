/**
 * @file StreamProcessorNode.hpp
 *
 * StreamProcessorNode is a class derived from 
 * Its purpose is to control and read status of the stream-
 * processor firmware, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_

#include "dtpcontrols/MonProbeNode.hpp"

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
  namespace dtpcontrols {

    class StreamProcessorNode : public uhal::Node {

      UHAL_DERIVEDNODE(StreamProcessorNode)
  
      public:
      explicit StreamProcessorNode(const uhal::Node& node);
      virtual ~StreamProcessorNode();

      const MonProbeNode& get_mon_probe_node(uint32_t i) const;

      int get_n_probes() const;

      // set stream to drop empty packets
      void drop_empty(bool dispatch=true) const;

      // get the TP threshold (all 64 channels)
      uint32_t get_threshold() const;

      // set the TP threshold (all 64 channels)
      void set_threshold(const uint32_t threshold, bool dispatch=true) const;

      // get the channel mask (all 64 channels)
      uint64_t get_channel_mask_all() const;

      // set the mask for all channels (all 64 channels)
      void set_channel_mask_all(uint64_t mask, bool dispatch=true) const;

      // set mask one channel
      void set_channel_mask(int channel, int mask) const;

      // get mask for one channel
      uint32_t get_channel_mask(int channel) const;

    private:
      uint32_t m_n_mon_probes;

    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_

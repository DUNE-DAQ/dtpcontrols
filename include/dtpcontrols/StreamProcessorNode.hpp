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

#define MASK_ENABLE 1
#define MASK_DISABLE 0

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class StreamProcessorNode : public uhal::Node {

  UHAL_DERIVEDNODE(StreamProcessorNode)
  
public:
  explicit StreamProcessorNode(const uhal::Node& );
  virtual ~StreamProcessorNode();

  void drop_empty(const bool);
  void set_mask_channels(const uint64_t, const bool, const bool);
  void set_mask_channel_00to31(const uint32_t, const bool, const bool);
  void set_mask_channel_32to63(const uint32_t, const bool,const bool);
  void cap_counters(const bool);
  void set_threshold(const uint32_t, const bool);
  const uhal::ValWord<uint32_t> get_mask_channel_00to31(const bool);
  const uhal::ValWord<uint32_t> get_mask_channel_32to63(const bool);

private:
  uint32_t m_n_mon_probes;
  
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_

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
  explicit StreamProcessorNode(const uhal::Node& );
  virtual ~StreamProcessorNode();

  const MonProbeNode& get_mon_probe_node(uint32_t i) const;

private:
  uint32_t m_n_mon_probes;

};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_STREAMPROCESSORNODE_HPP_

/**
 * @file MonProbeNode.hpp
 *
 * MonProbeNode is a class derived from 
 * Its purpose is to control and read status of the data-
 * reception firmware, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODE_HPP_

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class MonProbeNode : public uhal::Node {

  UHAL_DERIVEDNODE(MonProbeNode)
  
public:
  explicit MonProbeNode(const uhal::Node& );
  virtual ~MonProbeNode();

  uhal::ValWord<uint32_t> ready(bool dispatch=true);
  uhal::ValWord<uint32_t> valid(bool dispatch=true);
  uhal::ValWord<uint32_t> user(bool dispatch=true);
  uhal::ValWord<uint32_t> last(bool dispatch=true);
  uhal::ValWord<uint32_t> last_error(bool dispatch=true);
  uhal::ValWord<uint32_t> packet_count(bool dispatch=true);
  uhal::ValWord<uint32_t> axi_error(bool dispatch=true);
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODE_HPP_

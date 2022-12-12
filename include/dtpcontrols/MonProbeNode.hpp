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

#include "MonProbeNodeInfo.hpp"

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class MonProbeNode : public uhal::Node
{

  UHAL_DERIVEDNODE(MonProbeNode)

public:
  explicit MonProbeNode(const uhal::Node& node);
  virtual ~MonProbeNode();

  const MonProbeNodeInfo get_info() const; // retrieve monitor info from firmware
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODE_HPP_

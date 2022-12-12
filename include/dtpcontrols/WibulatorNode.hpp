/**
 * @file WibulatorNode.hpp
 *
 * DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

// dtpcontrols Headers
#include "dtpcontrols/toolbox.hpp"

// uHal Headers

#include "ers/Issue.hpp"
#include "uhal/DerivedNode.hpp"

// C++ Headers
#include <fstream>
#include <vector>

namespace dunedaq {
namespace dtpcontrols {

class WibulatorNode : public uhal::Node
{

  UHAL_DERIVEDNODE(WibulatorNode)

public:
  explicit WibulatorNode(const uhal::Node& node);
  virtual ~WibulatorNode();

  void write_pattern(std::vector<std::uint64_t>) const;
  std::vector<uint64_t> read_pattern() const;
  void fire() const;
  void set_fire(const uint32_t& fire_value, bool dispatch = true) const;
  uhal::ValWord<uint32_t> get_address_width(bool dispatch = true) const;
  uhal::ValWord<uint32_t> get_size(void) const;
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

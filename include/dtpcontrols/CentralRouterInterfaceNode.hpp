/**
 * @file CentralRouterInterfaceNode.hpp
 *
 * CentralRouterInterfaceNode is a class derived from DTPNode which
 * derives from uhal::Node.
 * Its purpose is to control and read status of the central-router-interface
 * firmware block, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_CENTRALROUTERINTERFACENODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_CENTRALROUTERINTERFACENODE_HPP_

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class CentralRouterInterfaceNode : public uhal::Node
{

  UHAL_DERIVEDNODE(CentralRouterInterfaceNode)

public:
  explicit CentralRouterInterfaceNode(const uhal::Node& node);
  virtual ~CentralRouterInterfaceNode();

  void enable(bool dispatch = true) const;
  void set_drop_empty(bool dispatch = true) const;
  uint32_t get_drop_empty() const;
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_CENTRALROUTERINTERFACENODE_HPP_

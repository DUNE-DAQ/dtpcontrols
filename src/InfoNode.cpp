/**
 * @file InfoNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/InfoNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(InfoNode)

//-----------------------------------------------------------------------------
InfoNode::InfoNode(const uhal::Node& node)
  : uhal::Node(node)
{}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
InfoNode::~InfoNode() {}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

} // namespace dtpcontrols
} // namespace dunedaq
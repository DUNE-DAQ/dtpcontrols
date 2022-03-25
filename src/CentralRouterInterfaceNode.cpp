/**
 * @file CentralRouterInterfaceNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/CentralRouterInterfaceNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(CentralRouterInterfaceNode)

CentralRouterInterfaceNode::CentralRouterInterfaceNode(const uhal::Node &node) : uhal::Node(node) {}

CentralRouterInterfaceNode::~CentralRouterInterfaceNode() {}

} // namespace dtpcontrols
} // namespace dunedaq

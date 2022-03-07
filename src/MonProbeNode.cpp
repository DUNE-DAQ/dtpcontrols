/**
 * @file MonProbeNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/MonProbeNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(MonProbeNode)

MonProbeNode::MonProbeNode(const uhal::Node& node) : uhal::Node(node) {}

MonProbeNode::~MonProbeNode(){}

} // namespace dtpcontrols
} // namespace dunedaq

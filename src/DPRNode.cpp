/**
 * @file DPRNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DPRNode.hpp"

#include <map>

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(DPRNode)

DPRNode::DPRNode(const uhal::Node& node) : uhal::Node(node) {}

DPRNode::~DPRNode() {}

} // namespace dtpcontrols
} // namespace dunedaq

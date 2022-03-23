/**
 * @file StreamProcessorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/StreamProcessorNode.hpp"
#include "dtpcontrols/MonProbeNode.hpp"
#include <algorithm>
#include <vector>

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(StreamProcessorNode)

StreamProcessorNode::StreamProcessorNode(const uhal::Node& node) : uhal::Node(node),
  m_n_mon_probes(6)
{
}

StreamProcessorNode::~StreamProcessorNode(){}

} // namespace dtpcontrols
} // namespace dunedaq

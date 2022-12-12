/**
 * @file MonProbeNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/MonProbeNode.hpp"

#include "logging/Logging.hpp"

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(MonProbeNode)

MonProbeNode::MonProbeNode(const uhal::Node& node)
  : uhal::Node(node)
{
}

MonProbeNode::~MonProbeNode() {}

const MonProbeNodeInfo
MonProbeNode::get_info() const
{

  TLOG_DEBUG(0) << "Getting monitor probe info";

  auto ready = getNode("ready").read();
  auto valid = getNode("valid").read();
  auto user = getNode("user").read();
  auto last = getNode("last").read();
  auto last_err = getNode("last_err").read();
  auto pkt_ctr = getNode("pkt_ctr").read();
  auto axi_err = getNode("axi_err").read();

  getClient().dispatch();

  MonProbeNodeInfo info;
  info.ready = int(ready);
  info.valid = int(valid);
  info.user = int(user);
  info.last = int(last);
  info.last_err = int(last_err);
  info.pkt_ctr = int(pkt_ctr);
  info.axi_err = int(axi_err);

  return info;
}

} // namespace dtpcontrols
} // namespace dunedaq

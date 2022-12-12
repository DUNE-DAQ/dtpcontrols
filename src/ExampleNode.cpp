/**
 * @file ExampleNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/ExampleNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(ExampleNode)

//-----------------------------------------------------------------------------
ExampleNode::ExampleNode(const uhal::Node& node)
  : uhal::Node(node)
{
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
ExampleNode::~ExampleNode() {}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
std::string
ExampleNode::get_status(bool print_out) const
{
  auto subnodes = read_sub_nodes(getNode("csr.stat"));
  std::stringstream status;

  for (auto& node : subnodes)
    status << node.first << " " << node.second.value();

  if (print_out)
    TLOG() << status.str();
  return status.str();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
std::map<std::string, uhal::ValWord<uint32_t>> // NOLINT(build/unsigned)
ExampleNode::read_sub_nodes(const uhal::Node& node, bool dispatch) const
{
  auto node_names = node.getNodes();

  std::map<std::string, uhal::ValWord<uint32_t>> node_name_value_pairs; // NOLINT(build/unsigned)

  for (auto it = node_names.begin(); it != node_names.end(); ++it)
    node_name_value_pairs[*it] = node.getNode(*it).read();
  if (dispatch)
    getClient().dispatch();
  return node_name_value_pairs;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void
ExampleNode::reset_sub_nodes(const uhal::Node& node, uint32_t aValue, bool dispatch) const // NOLINT(build/unsigned)
{

  auto node_names = node.getNodes();

  for (auto it = node_names.begin(); it != node_names.end(); ++it)
    node.getNode(*it).write(aValue);

  if (dispatch)
    getClient().dispatch();
}
//-----------------------------------------------------------------------------

} // namespace dtpcontrols
} // namespace dunedaq
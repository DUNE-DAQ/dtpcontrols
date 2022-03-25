/**
 * @file linkProcessorNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/LinkProcessorNode.hpp"

namespace dunedaq {
  namespace dtpcontrols {

    UHAL_REGISTER_DERIVED_NODE(LinkProcessorNode)

    LinkProcessorNode::LinkProcessorNode(const uhal::Node& node) : uhal::Node(node) { }

    LinkProcessorNode::~LinkProcessorNode() {}

    const DataRouterNode& LinkProcessorNode::get_data_router_node() const {
      return getNode<DataRouterNode>("drtr"); 
    }

    const StreamProcessorArrayNode& LinkProcessorNode::get_stream_proc_array_node() const {
      return getNode<StreamProcessorArrayNode>("stream_procs"); 
    }

  } // namespace dtpcontrols
} // namespace dunedaq


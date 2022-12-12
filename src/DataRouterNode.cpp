/**
 * @file DataRouterNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DataRouterNode.hpp"

#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/DPRNode.hpp"

namespace dunedaq {
  namespace dtpcontrols {
    
    UHAL_REGISTER_DERIVED_NODE(DataRouterNode)
    
    DataRouterNode::DataRouterNode(const uhal::Node& node) : uhal::Node(node) {}
    
    DataRouterNode::~DataRouterNode() {}
    
    const DataReceptionNode& DataRouterNode::get_data_reception_node(void) const {
      return getNode<DataReceptionNode>("dr");
    }
    
    const DPRNode& DataRouterNode::get_dpr_node(void) const {
      return getNode<DPRNode>("dpr");
    }
    
  } // namespace dtpcontrols
} // namespace dunedaq

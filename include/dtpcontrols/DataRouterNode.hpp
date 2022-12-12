/**
 * @file DataRouterNode.hpp
 *
 * DataRouterNode contains DataReception, DPR, and Unpacker blocks.
 * These receive data and transform it into packets for processing.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_DATAROUTERNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_DATAROUTERNODE_HPP_

#include "uhal/DerivedNode.hpp"

#include "dtpcontrols/DPRNode.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class DataRouterNode : public uhal::Node
{

  UHAL_DERIVEDNODE(DataRouterNode)

public:
  explicit DataRouterNode(const uhal::Node& node);
  virtual ~DataRouterNode();

  const DataReceptionNode& get_data_reception_node(void) const;
  const DPRNode& get_dpr_node(void) const;
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DATAROUTERNODE_HPP_

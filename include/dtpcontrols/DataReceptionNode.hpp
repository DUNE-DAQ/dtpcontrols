/**
 * @file DataReceptionNode.hpp
 *
 * DataReceptionNode is a class derived from 
 * Its purpose is to control and read status of the data-
 * reception firmware, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_DATARECEPTIONNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_DATARECEPTIONNODE_HPP_

#include "uhal/DerivedNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class DataReceptionNode : public uhal::Node {

  UHAL_DERIVEDNODE(DataReceptionNode)
  
public:
  explicit DataReceptionNode(const uhal::Node& node);
  virtual ~DataReceptionNode();

  void reset_input_word_counter(bool dispatch=true);
  void reset_output_word_counter(bool dispatch=true);
  void error_reset(bool dispatch=true);
  void reset(bool dispatch=true);

};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DATARECEPTIONNODE_HPP_

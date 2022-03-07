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
  explicit DataReceptionNode(const uhal::Node& );
  virtual ~DataReceptionNode();

  void enable_data_reception(bool);
  void reset_input_word_counter(bool);
  void reset_output_word_counter(bool);
  void error_reset(bool);
  uhal::ValWord<uint32_t> dual_port_ram_write_flag(bool);
  uhal::ValWord<uint32_t> stick_error_bit(bool);
  uhal::ValWord<uint32_t> back_pressure_bit(bool);
  uhal::ValWord<uint32_t> out_of_sync(bool);
  uhal::ValWord<uint32_t> rx_word_count(bool);
  uhal::ValWord<uint32_t> send_word_count(bool);
  uhal::ValWord<uint32_t> sent_packet_count(bool);
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DATARECEPTIONNODE_HPP_

/**
 * @file MonProbeNode.hpp
 *
 * MonProbeNode is a class derived from 
 * Its purpose is to control and read status of the data-
 * reception firmware, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODE_HPP_


#include "dtpcontrols/DTPNode.hpp"

class MonProbeNode : public DTPNode{

  UHAL_DERIVEDNODE(MonProbeNode)
  
public:
  explicit MonProbeNode(const uhal::Node& );
  virtual ~MonProbeNode();

  uhal::ValWord<uint32_t> Ready(bool);
  uhal::ValWord<uint32_t> Valid(bool);
  uhal::ValWord<uint32_t> User(bool);
  uhal::ValWord<uint32_t> Last(bool);
  uhal::ValWord<uint32_t> LastError(bool);
  uhal::ValWord<uint32_t> PacketCount(bool);
  uhal::ValWord<uint32_t> AXIError(bool);
};

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODE_HPP_
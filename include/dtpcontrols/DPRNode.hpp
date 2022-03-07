/**
 * @file DPRNode.hpp
 *
 * DPRNode is a class derived from
 * Its purpose is to control and read status of the DPR
 * firmware, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_DPRNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_DPRNODE_HPP_

#include "uhal/DerivedNode.hpp"

#include <string>

namespace dunedaq {
namespace dtpcontrols {

class DPRNode : public uhal::Node {

  UHAL_DERIVEDNODE(DPRNode)
  
public:
  explicit DPRNode(const uhal::Node& );
  virtual ~DPRNode();

  void set_mux_in(const uint32_t&, const bool);
  void set_mux_out(const uint32_t&, const bool);
  void SetMuxInOut(std::string&, const bool);
  void SetMuxInOut(const uint32_t &mux_in_choice,
		   const uint32_t &mux_out_choice, const bool dispatch);
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DPRNODE_HPP_

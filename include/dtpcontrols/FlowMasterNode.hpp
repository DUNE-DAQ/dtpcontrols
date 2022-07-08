/**
 * @file FlowMasterNode.hpp
 *
 * FlowMasterNode is a class derived from DTPNode which
 * derives from uhal::Node.
 * Its purpose is to control and read status of the flowmaster
 * firmware block, within DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_FLOWMASTERNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_FLOWMASTERNODE_HPP_

#include "dtpcontrols/toolbox.hpp"

#include "uhal/DerivedNode.hpp"

#include <vector>
#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {

class FlowMasterNode : public uhal::Node {

  UHAL_DERIVEDNODE(FlowMasterNode)
  
public:
  explicit FlowMasterNode(const uhal::Node& node);
  virtual ~FlowMasterNode();

  void set_source_gbt(bool dispatch=true) const;
  void set_source_wtor(bool dispatch=true) const;
  uint32_t get_source() const;

  void set_sink_hits(bool dispatch=true) const;
  void set_sink_link(const uint32_t link, bool dispatch=true) const;
  uint32_t get_sink() const;

};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_FLOWMASTERNODE_HPP_

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

#include "uhal/DerivedNode.hpp"

#include <vector>
#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {

class FlowMasterNode : public uhal::Node {

  UHAL_DERIVEDNODE(FlowMasterNode)
  
public:
  explicit FlowMasterNode(const uhal::Node& );
  virtual ~FlowMasterNode();

  void SourceSelect(const std::string&, const bool);
  void SourceSelect(const uint32_t&, const bool);  
  void SinkSelect(const std::string& , const bool);
  void SinkSelect(const uint32_t&, bool);

private:

  bool Exists(const uint32_t&, const std::vector<uint32_t>&);
  bool Exists(const std::string&, std::map<std::string, uint32_t>&);  

};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_FLOWMASTERNODE_HPP_

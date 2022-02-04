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

#include "dtpcontrols/DTPNode.hpp"

class FlowMasterNode : public DTPNode{

  UHAL_DERIVEDNODE(FlowMasterNode)
  
public:
  explicit FlowMasterNode(const uhal::Node& );
  virtual ~FlowMasterNode();

  void SourceSelect(const std::string&, const bool);
  void SinkSelect(const std::string& , bool);
};

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_FLOWMASTERNODE_HPP_

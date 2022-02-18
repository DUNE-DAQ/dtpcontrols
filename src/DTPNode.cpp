/**
 * @file DTPNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DTPNode.hpp"
#include <uhal/HwInterface.hpp>
#include <uhal/ValMem.hpp>

DTPNode::DTPNode(const uhal::Node &node) : uhal::Node(node) {};
DTPNode::~DTPNode(){};

std::map<std::string, uhal::ValWord<uint32_t>>
    DTPNode::GetFirmwareConfigInfo(uhal::HwInterface& Iface) {

  std::vector<std::string> infoNodes{Iface.getNodes("info.id.config")};
  std::map<std::string, uhal::ValWord<uint32_t>> ConfigVals;
  for (const auto& node : infoNodes) {
    ConfigVals.insert({node, getNode(node).read()});
  }
  getClient().dispatch();
  return ConfigVals;
  };

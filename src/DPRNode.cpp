/**
 * @file DPRNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DPRNode.hpp"

#include <map>

namespace dunedaq {
namespace dtpcontrols {

UHAL_REGISTER_DERIVED_NODE(DPRNode)

DPRNode::DPRNode(const uhal::Node& node) : uhal::Node(node) {}

DPRNode::~DPRNode() {}

void DPRNode::set_mux_in(const uint32_t &mux_in_choice, const bool dispatch) {
  if (mux_in_choice == 0 || 1) getNode("csr.ctrl.config.mux_in").write(mux_in_choice);
  if (dispatch) getClient().dispatch();
}

void DPRNode::set_mux_out(const uint32_t &mux_out_choice, const bool dispatch) {
  if (mux_out_choice == 0 || 1) getNode("csr.ctrl.config.mux_out").write(mux_out_choice);
  if (dispatch) getClient().dispatch();
}

void DPRNode::SetMuxInOut(std::string &mux_choice, const bool dispatch) {
  const std::vector<std::string> mux_choices {"reset", "playback", "sink", "passthrough"};
  std::map<std::string, uint32_t> mux_in {{"reset", 0}, {"playback", 0}, {"sink", 1}, {"passthrough", 1}};
  std::map<std::string, uint32_t> mux_out {{"reset", 0}, {"playback", 1}, {"sink", 0}, {"passthrough", 1}};  
  if (std::find(mux_choices.begin(), mux_choices.end(), mux_choice) != mux_choices.end()) {
    getNode("csr.ctrl.config.mux_in").write(mux_in[mux_choice]);
    getNode("csr.ctrl.config.mux_in").write(mux_out[mux_choice]);
    if(dispatch) getClient().dispatch();
  }
  else{} //placeholder for ERS
}

} // namespace dtpcontrols
} // namespace dunedaq

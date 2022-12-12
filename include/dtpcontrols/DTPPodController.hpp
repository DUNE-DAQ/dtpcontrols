/**
 * @file DTPPodController.hpp
 *
 * Top level DTP Pod
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODCONTROLLER_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODCONTROLLER_HPP_

// dtpcontrols Headers
#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/FlowMasterNode.hpp"
#include "dtpcontrols/InfoNode.hpp"
#include "dtpcontrols/LinkProcessorNode.hpp"
#include "dtpcontrols/MonProbeNodeInfo.hpp"
#include "dtpcontrols/OutputSinkNode.hpp"
#include "dtpcontrols/WibulatorNode.hpp"

// uHal Headers
#include "ers/Issue.hpp"
#include "uhal/DerivedNode.hpp"

// C++ Headers
#include <chrono>
#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {

class DTPPodController
{
public:
  explicit DTPPodController(uhal::HwInterface);
  virtual ~DTPPodController();

  uint get_n_links() const;
  uint get_n_streams() const;
  uint get_n_mux() const;
  uint get_wibtors_width() const;
  uint get_outsink_width() const;
  bool get_wibtors_en() const;
  bool get_outsink_en() const;

  // get nodes
  const uhal::Node& get_node() const;
  const InfoNode& get_info_node() const;
  const ControlNode& get_control_node() const;
  const FlowMasterNode& get_flowmaster_node() const;
  const WibulatorNode& get_wibulator_node(uint i) const;
  const LinkProcessorNode& get_link_processor_node(uint i) const;
  const CentralRouterInterfaceNode& get_crif_node() const;
  const OutputSinkNode& get_output_sink_node() const;

  // reset everything
  void reset() const;

  // reset counters
  void reset_counters() const;

  // set all thresholds
  void set_threshold_all(uint threshold) const;

  // reset all masks
  void reset_masks() const;

  // set masks for all channels in one link/pipe
  void set_channel_mask(uint link, uint pipe, uint64_t mask) const;

  // mask one channel
  void mask_channel(uint link, uint pipe, uint channel) const;

  // get mon probe info
  std::vector<MonProbeNodeInfo> get_mon_probe_info(uint link, uint pipe) const;

private:
  void load_fw_info();

  // firware config info this build contains
  std::map<std::string, uint32_t> m_fw_info;

  uhal::HwInterface m_hw;
  const uhal::Node& m_pod;
  //
  uint m_n_links = 0;
  uint m_n_streams = 0;
  uint m_n_mux = 0;
  uint m_wibtors_width = 0;
  uint m_outsink_width = 0;
  bool m_wibtors_en = false;
  bool m_outsink_en = false;
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODCONTROLLER_HPP_

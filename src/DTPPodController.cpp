/**
 * @file DTPPodController.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <map>
#include <string>

#include "dtpcontrols/DTPPodController.hpp"
#include "logging/Logging.hpp"

namespace dunedaq {
namespace dtpcontrols {

DTPPodController::DTPPodController(uhal::HwInterface hw)
  : m_hw(hw)
  , m_pod(m_hw.getNode())
{

  TLOG_DEBUG(1) << "DTPPodController built ";

  load_fw_info();
}

DTPPodController::~DTPPodController() {}

void
DTPPodController::load_fw_info()
{
  auto m_fw_info = get_info_node().get_firmware_config_info();
  m_n_links = m_fw_info["n_links"];
  m_n_streams = m_fw_info["n_port"];
  m_n_mux = m_fw_info["n_mux"];
  m_wibtors_en = m_fw_info["wibtors_en"];
  m_outsink_en = m_fw_info["outsink_en"];
  m_wibtors_width = m_fw_info["wibtors_width"];
  m_outsink_width = m_fw_info["outsink_width"];
}

uint
DTPPodController::get_n_links() const
{
  return m_n_links;
}

uint
DTPPodController::get_n_streams() const
{
  return m_n_streams;
}

uint
DTPPodController::get_n_mux() const
{
  return m_n_mux;
}

uint
DTPPodController::get_wibtors_width() const
{
  return m_wibtors_width;
}

uint
DTPPodController::get_outsink_width() const
{
  return m_outsink_width;
}

bool
DTPPodController::get_wibtors_en() const
{
  return m_wibtors_en;
}

bool
DTPPodController::get_outsink_en() const
{
  return m_outsink_en;
}

const uhal::Node&
DTPPodController::get_node() const
{
  return m_pod;
}

const InfoNode&
DTPPodController::get_info_node() const
{
  return m_pod.getNode<InfoNode>("info");
}

const ControlNode&
DTPPodController::get_control_node() const
{
  return m_pod.getNode<ControlNode>("ctrl");
}

const FlowMasterNode&
DTPPodController::get_flowmaster_node() const
{
  return m_pod.getNode<FlowMasterNode>("flowmaster");
}

const LinkProcessorNode&
DTPPodController::get_link_processor_node(uint i) const
{
  if (i < get_n_links()) {
    std::string name("linkproc");
    name += std::to_string(i);
    return m_pod.getNode<LinkProcessorNode>(name);
  } else {
    throw std::out_of_range("Link id out of bounds");
  }
}

const WibulatorNode&
DTPPodController::get_wibulator_node(uint i) const
{
  if (i < get_n_links()) {
    std::string name("wibtor");
    name += std::to_string(i);
    return m_pod.getNode<WibulatorNode>(name);
  } else {
    // replace with ERS exception
    throw std::out_of_range("Wibulator id out of bounds");
  }
}

const CentralRouterInterfaceNode&
DTPPodController::get_crif_node() const
{
  return m_pod.getNode<CentralRouterInterfaceNode>("cr_if");
}

const OutputSinkNode&
DTPPodController::get_output_sink_node() const
{
  return m_pod.getNode<OutputSinkNode>("outsink");
}

void
DTPPodController::reset() const
{
  auto ctrl_node = get_control_node();
  ctrl_node.soft_reset(true);
  ctrl_node.master_reset(true);

  /*      for (uint i=0; i!=m_n_links; ++i) {
auto lDataReceptionNode =
get_link_processor_node(i).get_data_router_node().get_data_reception_node();
lDataReceptionNode.reset(true);
} */
}

void
DTPPodController::reset_counters() const
{
}

void
DTPPodController::set_threshold_all(uint threshold) const
{
  for (uint i_link = 0; i_link != get_n_links(); ++i_link) {
    for (uint i_stream = 0; i_stream != get_n_streams(); ++i_stream) {
      uint32_t il = static_cast<uint32_t>(i_link);
      uint32_t is = static_cast<uint32_t>(i_stream);
      auto l_sa_node = get_link_processor_node(il).get_stream_proc_array_node();
      l_sa_node.stream_select(is, false);
      l_sa_node.get_stream_proc_node().set_threshold(threshold, false);
    }
  }

  m_pod.getClient().dispatch();
}

std::vector<MonProbeNodeInfo>
DTPPodController::get_mon_probe_info(uint link, uint stream) const
{
  std::vector<MonProbeNodeInfo> tmp;

  auto l_sa_node = get_link_processor_node(link).get_stream_proc_array_node();

  // capture counters
  l_sa_node.getNode("csr.ctrl.cap_ctrs").write(0x1);
  l_sa_node.getNode("csr.ctrl.cap_ctrs").write(0x0);
  l_sa_node.getClient().dispatch();

  // select link
  l_sa_node.stream_select(stream, true);
  l_sa_node.getClient().dispatch();

  // loop over probes
  uint n_probes = l_sa_node.get_stream_proc_node().get_n_probes();

  for (uint i_probe = 0; i_probe != n_probes; ++i_probe) {
    uint32_t ip = static_cast<uint32_t>(i_probe);
    MonProbeNodeInfo info = l_sa_node.get_stream_proc_node().get_mon_probe_node(ip).get_info();

    info.link = link;
    info.stream = stream;
    info.probe = i_probe;

    tmp.push_back(info);
  }

  return tmp;
}

} // namespace dtpcontrols
} // namespace dunedaq

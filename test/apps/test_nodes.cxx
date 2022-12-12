/**
 * @file test_nodes.cxx
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <iostream>

#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/DTPPodController.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/toolbox.hpp"
#include "logging/Logging.hpp"
#include "uhal/uhal.hpp"

using namespace uhal;
using namespace dunedaq::dtpcontrols;

int main(int argc, char const* argv[]) {
  TLOG() << "Test TPG Node structure";

  std::string conn_file = find_connection_file();
  std::string device("flx-0-p2-hf");

  // optional command line args
  if (argc > 1) {
    device = argv[1];
  }

  if (argc > 2) {
    conn_file = std::string(argv[2]);
  }

  TLOG() << "Connections : " << conn_file;
  TLOG() << "Device      : " << device;

  //  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  // uhal::HwInterface flx = cm.getDevice(device);

  auto pod_ctrl = DTPPodController(cm.getDevice(device));

  auto lInfoNode = pod_ctrl.get_info_node();
  TLOG() << lInfoNode.getId();
  auto lCtrlNode = pod_ctrl.get_control_node();
  TLOG() << lCtrlNode.getId() << std::endl;

  auto lFlowMasterNode = pod_ctrl.get_flowmaster_node();
  TLOG() << lFlowMasterNode.getId();

  for (int i = 0; i < 5; ++i) {
    auto lWibtorNode = pod_ctrl.get_wibulator_node(i);
    TLOG() << lWibtorNode.getId();
    auto lLinkProcNode = pod_ctrl.get_link_processor_node(i);
    TLOG() << lLinkProcNode.getId();
  }

  auto lCrifNode = pod_ctrl.get_crif_node();
  TLOG() << lCrifNode.getId();
  auto lOutsinkNode = pod_ctrl.get_output_sink_node();
  TLOG() << lOutsinkNode.getId();
}

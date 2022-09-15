/**
 * @file test_fw_config.cxx
 *
 * Test configuration of DUNE TP firmware
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <iostream>
#include <string>
#include <vector>

#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/DTPPodController.hpp"
#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/toolbox.hpp"
#include "logging/Logging.hpp"
#include "uhal/uhal.hpp"

using namespace uhal;
using namespace dunedaq::dtpcontrols;

int main(int argc, char const* argv[]) {
  // default options
  std::string conn_file = find_connection_file();
  std::string device("flx-0-p2-hf");
  uint32_t threshold(20);
  std::vector<uint64_t> masks(10, 0);
  bool verbose = false;

  // get options
  const std::vector<std::string_view> args(argv + 1, argv + argc);
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    // device name
    if (*it == "-d") {
      device = *(it + 1);
    }

    // connection file
    if (*it == "-c") {
      conn_file = *(it + 1);
    }

    // verbose mode
    if (*it == "-v") {
      verbose = true;
    }

    // TP threshold
    if (*it == "-t") {
      threshold = std::stoi(std::string(*(it + 1)));
    }

    // comma-separated list of channels to mask
    if (*it == "-m") {
      std::string_view m(*(it + 1));
      // parse the list of channels to be masked

      // to do
    }

    // help
    if (*it == "-h") {
      std::cout << "\nUsage:\n dtpcontrols_test_config [options]\n\n";
      std::cout << "Options:\n";
      std::cout << "  -c <filename>\t\tconnection file name\n";
      std::cout << "  -d <device>\t\tdevice name\n";
      std::cout << "  -v \t\t\tverbose mode\n";
      std::cout << "  -t <threshold>\tTP threshold\n";
      std::cout << "  -m <mask>\t\tcomma-separated list of channels to mask\n";
      exit(0);
    }
  }

  // verbose output (mainly uHAL debug mode)
  if (verbose) {
    uhal::setLogLevelTo(uhal::Debug());
  }

  // setup connections/device
  TLOG() << "FLX-TPG FW configuration";
  TLOG() << "Connections : " << conn_file;
  TLOG() << "Device      : " << device;

  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  // uhal::HwInterface flx = cm.getDevice(device);

  // get the TP node
  DTPPodController pod_ctrl(cm.getDevice(device));

  // set source to wibulator
  TLOG() << "Setting source to wibulator (flowmaster.csr.ctrl.gbt_src)" << std::endl;
  pod_ctrl.get_flowmaster_node().set_source_wtor();

  // read back value
  uint32_t gbt_src = pod_ctrl.get_flowmaster_node().get_source();
  TLOG() << "Source select (flowmaster.csr.ctrl.gbt_src) : " << std::hex << int(gbt_src) << std::endl;

  // set sink to hits
  TLOG() << "Setting sink to hits (flowmaster.csr.ctrl.sink_src)" << std::endl;
  pod_ctrl.get_flowmaster_node().set_sink_hits(true);

  // read back value
  uint32_t sink_src = pod_ctrl.get_flowmaster_node().get_sink();
  TLOG() << "Sink select (flowmaster.csr.ctrl.sink_src) : " << std::hex << int(sink_src) << std::endl;

  // enable CRIF
  pod_ctrl.get_crif_node().enable(true);

  // set CRIF to drop empty packets
  pod_ctrl.get_crif_node().set_drop_empty(true);

  // read back value
  uint32_t crif_de = pod_ctrl.get_crif_node().get_drop_empty();
  TLOG() << "CRIF drop-empty (crif.csr.ctrl.drop_empty) : " << std::hex << int(crif_de) << std::endl;

  // set thresolds
  int n_links = pod_ctrl.get_n_links();
  int n_streams = pod_ctrl.get_n_streams();
  for (int i = 0; i < n_links; ++i) {
    for (int j = 0; i < n_streams; ++j) {
      pod_ctrl.get_link_processor_node(i).set_threshold(j, 20);
    }
  }

  // setup each link
  for (int i = 0; i < n_links; ++i) {
    pod_ctrl.get_link_processor_node(i).setup(true, true);
  }
}

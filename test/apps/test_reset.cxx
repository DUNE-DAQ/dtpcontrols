/**
 * @file test_fw_reset.cxx
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/DTPPodNode.hpp"
#include "dtpcontrols/toolbox.hpp"

#include "uhal/uhal.hpp"
#include "logging/Logging.hpp"

#include <iostream>

using namespace uhal;
using namespace dunedaq::dtpcontrols;

int main(int argc, char const* argv[]) {

dunedaq::logging::Logging::setup();

  // default options
  std::string conn_file = find_connection_file();
  std::string device("flx-0-p2-hf");

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

    // help
    if (*it == "-h") {
      std::cout << "\nUsage:\n dtpcontrols_test_reset [options]\n\n";
      std::cout << "Options:\n";
      std::cout << "  -c <filename>\tconnection file name\n";
      std::cout << "  -d <device>\tdevice name\n";      
      exit(0);
    }

  }

  TLOG() << "FLX-TPG FW reset";
  TLOG() << "Connections : " << conn_file;
  TLOG() << "Device      : " << device;

  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(device);

DTPPodNode dtp_pod_node (flx.getNode());
dtp_pod_node.reset();


}


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

  TLOG() << "FLX-TPG FW reset";

  std::string conn_file = find_connection_file();
  std::string device("");

  if (argc >1) {
    device = argv[1];
  }
  else {
    TLOG() << "At least specify a device";
  }

  if (argc > 2) {
    conn_file = std::string(argv[2]);
  }
  
  TLOG() << "Connections : " << conn_file;
  TLOG() << "Device      : " << device;

  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(std::string(argv[1]));

  DTPPodNode dtp_pod_node (flx.getNode());
  dtp_pod_node.reset();
  
}


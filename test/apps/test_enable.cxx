/**
 * @file test_fw_enable.cxx
 * 
 * Test configuration of DUNE TP firmware
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
#include <string>
#include <vector>

using namespace uhal;
using namespace dunedaq::dtpcontrols;


int main(int argc, char const* argv[]) {

  TLOG() << "FLX-TPG FW configuration";

  // default options
  std::string conn_file = find_connection_file();
  std::string device("flx-0-p2-hf");
  bool disable = false;

  // get options
  const std::vector<std::string_view> args(argv + 1, argv + argc);
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {

    // device name
    if (*it == "-d") { // || *it = "--device") {
      device = *(it + 1);
    }

    // connection file
    if (*it == "-c") { // || *it == "--connection") {
      conn_file = *(it + 1);
    }

    // disable
    if (*it =="-s") { // ||*it =="--disable") {
      disable = true;
    }

  }

  // setup connections/device
  TLOG() << "Connections : " << conn_file;
  TLOG() << "Device      : " << device;

  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(device);

  // get the TP node
  DTPPodNode dtp_pod_node (flx.getNode());

  // configure it
  if (disable) {
    dtp_pod_node.disable();
  }
  else {
    dtp_pod_node.enable();
  }

}


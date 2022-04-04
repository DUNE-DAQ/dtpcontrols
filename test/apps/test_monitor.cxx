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

  TLOG() << "FLX-TPG FW monitor";

  // default options
  std::string conn_file = find_connection_file();
  std::string device("flx-0-p2-hf");
  int period(5);
  bool debug=false;

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

    // period between reads
    if (*it =="-s") { // ||*it =="--disable") {
      period = std::stoi( std::string(*(it + 1)) );
    }

    // debug mode
    if (*it =="-debug") { // ||*it =="--disable") {
      debug = true;
    }

  }

  // setup connections/device
  TLOG() << "Connections : " << conn_file;
  TLOG() << "Device      : " << device;

  if (debug) {
    uhal::setLogLevelTo(uhal::Debug());
  }
  
  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(device);

  // get the TP node
  DTPPodNode dtp_pod_node (flx.getNode());

  // monitor it
  while (true) {

    std::vector<MonProbeNodeInfo> info = dtp_pod_node.get_info();

    std::stringstream out;

    for (auto i=0; i!=6; i++) {

      out << "| " << i;

      out << " | " << info.at(i).pkt_ctr;

      if (info.at(i).ready > 0) {
	out << " [rdy] ";
      }
      else {
	out << " [bsy] ";
      }  
      
      out << info.at(i).last_err ;

    }

    std::cout << out;

    sleep(period);
  }

}


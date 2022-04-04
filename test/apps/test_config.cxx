/**
 * @file test_fw_config.cxx
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
  uint32_t threshold(20);
  std::vector<uint64_t> masks(10, 0);
  bool verbose=false;

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
    if (*it =="-t") {
      threshold = std::stoi( std::string(*(it + 1)) );
    }

    // comma-separated list of channels to mask
    if (*it =="-m") {
      std::string_view m( *(it + 1) );
      // parse the list of channels to be masked
      
      // to do
    }

  }

  // verbose output (mainly uHAL debug mode)
  if (verbose) { uhal::setLogLevelTo(uhal::Debug()); }

  // setup connections/device
  TLOG() << "Connections : " << conn_file;
  TLOG() << "Device      : " << device;

  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(device);

  // get the TP node
  DTPPodNode dtp_pod_node (flx.getNode());

  // set source to wibulator
  dtp_pod_node.set_source_int();

  // read back value
  auto gbt_src = dtp_pod_node.getNode("flowmaster.csr.ctrl.gbt_src").read();
  dtp_pod_node.getClient().dispatch();
  TLOG()  << "Source select (flowmaster.csr.ctrl.gbt_src) : " << std::hex << int(gbt_src) <<std::endl;

  // set sink to hits
  dtp_pod_node.set_sink_hits();
  
  // read back value
  auto sink_src = dtp_pod_node.getNode("flowmaster.csr.ctrl.sink_src").read();
  dtp_pod_node.getClient().dispatch();
  TLOG()  << "Sink select (flowmaster.csr.ctrl.sink_src) : " << std::hex << int(sink_src) <<std::endl;


  // set CRIF to drop empty packets
  dtp_pod_node.set_crif_drop_empty();
      
  // read back value
  auto crif_de = dtp_pod_node.getNode("cr_if.csr.ctrl.drop_empty").read();
  dtp_pod_node.getClient().dispatch();
  TLOG()  << "CRIF drop-empty (crif.csr.ctrl.drop_empty) : " << std::hex << int(crif_de) <<std::endl;  

  // setup each link
  dtp_pod_node.setup_processors();
  
  // set TP threshold
  dtp_pod_node.set_threshold_all(threshold);


}


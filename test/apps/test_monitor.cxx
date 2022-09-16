/**
 * @file test_fw_enable.cxx
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
  TLOG() << "FLX-TPG FW monitor";

  // default options
  std::string conn_file = find_connection_file();
  std::string device("flx-0-p2-hf");
  int period = 2;
  int n_links = 5;
  int n_pipes = 4;
  bool verbose = false;

  // get options
  const std::vector<std::string_view> args(argv + 1, argv + argc);
  for (auto it = args.begin(), end = args.end(); it != end; ++it) {
    // device name
    if (*it == "-d") {  // || *it = "--device") {
      device = *(it + 1);
    }

    // connection file
    if (*it == "-c") {  // || *it == "--connection") {
      conn_file = *(it + 1);
    }

    // verbose mode
    if (*it == "-v") {
      verbose = true;
    }

    // link
    if (*it == "-l") {  // ||*it =="--disable") {
      n_links = std::stoi(std::string(*(it + 1)));
    }

    // pipe
    if (*it == "-p") {  // ||*it =="--disable") {
      n_pipes = std::stoi(std::string(*(it + 1)));
    }

    // period between reads
    if (*it == "-s") {  // ||*it =="--disable") {
      period = std::stoi(std::string(*(it + 1)));
    }

    // help
    if (*it == "-h") {
      std::cout << "\nUsage:\n dtpcontrols_test_monitor [options]\n\n";
      std::cout << "Options:\n";
      std::cout << "  -c <filename>\tconnection file name\n";
      std::cout << "  -d <device>\tdevice name\n";
      std::cout << "  -v \t\tverbose mode\n";
      std::cout << "  -l <n_links> \t number of links\n";
      std::cout << "  -p <n_pipes> \t number of pipes\n";
      std::cout << "  -s <period> \t time between reads\n";
      exit(0);
    }
  }

  // verbose mode
  if (verbose) {
    uhal::setLogLevelTo(uhal::Debug());
  }

  // setup connections/device
  TLOG() << "Connections : " << conn_file;
  TLOG() << "Device      : " << device;

  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  // uhal::HwInterface flx = cm.getDevice(device);

  // get the TP node
  DTPPodController dtp_ctrl(cm.getDevice(device));

  // monitor it
  while (true) {
    std::stringstream out;
    out << std::endl;

    // loop over enabled links
    for (int i_link = 0; i_link < n_links; ++i_link) {
      out << "Link processor : " << i_link << std::endl;

      std::vector<std::vector<MonProbeNodeInfo> > infos;

      // loop over pipes
      for (int i_pipe = 0; i_pipe < n_pipes; ++i_pipe) {
        std::vector<MonProbeNodeInfo> info = dtp_ctrl.get_mon_probe_info(i_link, i_pipe);
        infos.push_back(info);
      }

      // display info
      for (int i_p = 0; i_p != 6; i_p++) {
        out << "| probe " << i_p << " | ";

        for (int i_pipe = 0; i_pipe != n_pipes; i_pipe++) {
          // one cell
          out << infos.at(i_pipe).at(i_p).pkt_ctr;

          if (infos.at(i_pipe).at(i_p).ready > 0) {
            out << " [rdy] ";
          } else {
            out << " [bsy] ";
          }

          out << infos.at(i_pipe).at(i_p).last_err << " | ";
        }

        out << std::endl;
      }
    }

    out << std::endl;

    TLOG() << out.str();

    sleep(period);
  }
}

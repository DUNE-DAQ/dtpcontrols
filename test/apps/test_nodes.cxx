#include "dtpcontrols/DataReceptionNode.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/DTPPodNode.hpp"
#include "dtpcontrols/toolbox.hpp"

#include "uhal/uhal.hpp"

#include <iostream>

using namespace uhal;
using namespace dunedaq::dtpcontrols;

int main(int argc, char const* argv[]) {

  std::cout << "Test TPG Node structure" << std::endl;

  std::string conn_file = find_connection_file();
  std::string device("flx-0-p2-hf");

  // optional command line args
  if (argc > 1) {
    device = argv[1];
  }

  if (argc > 2) {
    conn_file = std::string(argv[2]);
  }
  
  std::cout << "Connections : " << conn_file << std::endl;
  std::cout << "Device      : " << device << std::endl;

  //  uhal::setLogLevelTo(uhal::Debug());
  uhal::ConnectionManager cm(conn_file, {"ipbusflx-2.0"});
  uhal::HwInterface flx = cm.getDevice(device);

  auto dtp_pod_node = dynamic_cast<const DTPPodNode*>( &flx.getNode(std::string("")) );
  
  auto lInfoNode = dtp_pod_node->get_info_node();
  std::cout << lInfoNode.getId() << std::endl;
  auto lCtrlNode = dtp_pod_node->get_control_node();
  std::cout << lCtrlNode.getId() << std::endl;

  auto lFlowMasterNode = dtp_pod_node->get_flowmaster_node();
  std::cout << lFlowMasterNode.getId() << std::endl;

  for (int i=0; i<5; ++i) {
    auto lWibtorNode = dtp_pod_node->get_wibulator_node(i);
    std::cout << lWibtorNode.getId() << std::endl;
    auto lLinkProcNode = dtp_pod_node->get_link_processor_node(i);
  std::cout << lLinkProcNode.getId() << std::endl;
  }

  auto lCrifNode = dtp_pod_node->get_crif_node();
  std::cout << lCrifNode.getId() << std::endl;
  auto lOutsinkNode = dtp_pod_node->get_output_sink_node();
  std::cout << lOutsinkNode.getId() << std::endl;
  
}


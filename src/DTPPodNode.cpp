/**
 * @file DTPPodNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DTPPodNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
  namespace dtpcontrols {
    
    UHAL_REGISTER_DERIVED_NODE(DTPPodNode)
    
    DTPPodNode::DTPPodNode(const uhal::Node& node) :uhal::Node(node),
      m_n_links(5)
    {
    }

    DTPPodNode::~DTPPodNode() {}

    const InfoNode& DTPPodNode::get_info_node() const {
      return getNode<InfoNode>("info");
    }

    const ControlNode& DTPPodNode::get_control_node() const {
      return getNode<ControlNode>("ctrl");
    }

    const FlowMasterNode& DTPPodNode::get_flowmaster_node() const {
      return getNode<FlowMasterNode>("flowmaster");
    }
    
    const LinkProcessorNode& DTPPodNode::get_link_processor_node(uint32_t i) const {
      if (i < m_n_links) {
	std::string name("linkproc");
	name += std::to_string(i);
	return getNode<LinkProcessorNode>(name);
      }
      else {
	//throw
      }
    }

    const WibulatorNode& DTPPodNode::get_wibulator_node(uint32_t i) const {
      if (i < m_n_links) {
	std::string name("wibtor");
	name += std::to_string(i);
	return getNode<WibulatorNode>(name);
      }
      else {
	//throw
      }
    }

    const CentralRouterInterfaceNode& DTPPodNode::get_crif_node() const {
      return getNode<CentralRouterInterfaceNode>("cr_if");
    }

    const OutputSinkNode& DTPPodNode::get_output_sink_node() const {
      return getNode<OutputSinkNode>("outsink");
    }

    std::map<std::string, uint32_t> DTPPodNode::get_firmware_config_info() const {
      auto info_node = get_info_node();
      auto l_config_names = info_node.getNode("config").getNodes();
      std::map<std::string, uint32_t> l_firmware_info;
      for (auto& l_name : l_config_names) {
	std::cout << l_name <<std::endl;
	auto temp = info_node.getNode("config."+l_name).read();
	getClient().dispatch();
	l_firmware_info.insert({l_name, temp});
	}
      return l_firmware_info;
    }

    void DTPPodNode::reset() {
      m_dtp_fw_info = get_firmware_config_info();
      m_n_links = m_dtp_fw_info["n_links"];
      auto lCtrlNode = get_control_node();
      lCtrlNode.soft_reset(true);
      lCtrlNode.master_reset(true);   

      for (uint i=0; i!=m_n_links; ++i) {	
	auto lDataReceptionNode = get_link_processor_node(i).get_data_router_node().get_data_reception_node();
	lDataReceptionNode.reset(true);
      }

    }
    
  } // namespace dtpcontrols
} // namespace dunedaq

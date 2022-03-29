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
    
    DTPPodNode::DTPPodNode(const uhal::Node& node) :uhal::Node(node)
    {
      //values from
      //https://gitlab.cern.ch/dune-daq/readout/dtp-firmware/-/blob/dtp-v2.0.0/projects/ultimate/firmware/sim_hdl/dtpc_params.vhd
      TLOG_DEBUG(1) << "DTPPodNode initialising ";
      set_n_links(5);
      set_n_port(4);
      set_n_mux(64);
      set_wibtors_width(13);
      set_outsink_width(13);
      set_wibtors_en(true);
      set_outsink_en(true);
    }

    DTPPodNode::~DTPPodNode() {}

    void DTPPodNode::set_n_links(uint32_t n_links) {
      m_n_links = n_links;
      TLOG_DEBUG(1) << "Number of links set to " << m_n_links;
    }

    void DTPPodNode::set_n_port(uint32_t n_port) {
      m_n_port = n_port;
      TLOG_DEBUG(1) << "Number of ports set to " << m_n_port;
    }

    void DTPPodNode::set_n_mux(uint32_t n_mux) {
      m_n_mux = n_mux;
      TLOG_DEBUG(1) << "Number of mux set to " << m_n_links;
    }

    void DTPPodNode::set_wibtors_width(uint32_t wibtors_width) {
      m_wibtors_width = wibtors_width;
      TLOG_DEBUG(1) << "Wibulator width set to " << m_wibtors_width;
    }

    void DTPPodNode::set_outsink_width(uint32_t outsink_width) {
      m_outsink_width = outsink_width;
      TLOG_DEBUG(1) << "Outsink width set to " << m_wibtors_width;
    }    

    void DTPPodNode::set_wibtors_en(uint32_t wibtors_en) {
      m_wibtors_en = wibtors_en;
      TLOG_DEBUG(1) << "Wibulator enable set to " << m_wibtors_en;
    }

    void DTPPodNode::set_outsink_en(uint32_t outsink_en) {
      m_outsink_en = outsink_en;
      TLOG_DEBUG(1) << "Outsink enable set to " << m_outsink_en;
    }        
    
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
    
    void DTPPodNode::reset() const {
    
      auto lCtrlNode = get_control_node();
      lCtrlNode.soft_reset(true);

      for (uint i=0; i!=m_n_links; ++i) {	
	auto lDataReceptionNode = get_link_processor_node(i).get_data_router_node().get_data_reception_node();
	lDataReceptionNode.reset(true);
      }

    }
    
    void DTPPodNode::configure(uint32_t threshold, std::vector<uint64_t> masks) const {

      // set source to gbt (links)
      auto lFlowMasterNode = get_flowmaster_node();
      lFlowMasterNode.source_select("gbt", true);
      lFlowMasterNode.sink_select("hits", true);

      // set CRIF to drop empty packets
      auto lCRIFNode = get_crif_node();
      lCRIFNode.drop_empty(false);

      // configure link processors
      for (uint32_t i=0; i!=m_n_links; ++i) {

	// enable data reception
	auto l_dr_node = get_link_processor_node(i).get_data_router_node();
	l_dr_node.get_data_reception_node().enable(false);

	// set DPR mux
	auto l_dpr_node = l_dr_node.get_dpr_node();
	l_dpr_node.set_mux_in(0x1);
	l_dpr_node.set_mux_out(0x1);

	// configure pipelines
	for (uint32_t j=0; j!=m_n_port; ++j) {

	  auto l_sa_node = get_link_processor_node(i).get_stream_proc_array_node();
	  l_sa_node.stream_select(j, false);

	  // set drop empty
	  l_sa_node.get_stream_proc_node().drop_empty(false);

	  // set hitfinder threshold
	  l_sa_node.get_stream_proc_node().set_threshold(threshold, false);

	  // set masks
	  uint64_t mask = masks[i*m_n_port + j];
	  l_sa_node.get_stream_proc_node().set_mask_channels(mask, false);

	}

      }

      getClient().dispatch();

      // and read it all back
      


    }

    void DTPPodNode::enable() const {

      auto lCRIFNode = get_crif_node();
      lCRIFNode.getNode("csr.ctrl.en").write(0x1);
      getClient().dispatch();
   
    }

    void DTPPodNode::disable() const {

      auto lCRIFNode = get_crif_node();
      lCRIFNode.getNode("csr.ctrl.en").write(0x0);
      getClient().dispatch();

    }


  } // namespace dtpcontrols
} // namespace dunedaq

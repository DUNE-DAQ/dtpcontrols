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

    void DTPPodNode::set_n_links(int n_links) {
      m_n_links = n_links;
      TLOG_DEBUG(1) << "Number of links set to " << m_n_links;
    }

    void DTPPodNode::set_n_port(int n_streams) {
      m_n_streams = n_streams;
      TLOG_DEBUG(1) << "Number of streams set to " << m_n_streams;
    }

    void DTPPodNode::set_n_mux(int n_mux) {
      m_n_mux = n_mux;
      TLOG_DEBUG(1) << "Number of mux set to " << m_n_links;
    }

    void DTPPodNode::set_wibtors_width(int wibtors_width) {
      m_wibtors_width = wibtors_width;
      TLOG_DEBUG(1) << "Wibulator width set to " << m_wibtors_width;
    }

    void DTPPodNode::set_outsink_width(int outsink_width) {
      m_outsink_width = outsink_width;
      TLOG_DEBUG(1) << "Outsink width set to " << m_wibtors_width;
    }    

    void DTPPodNode::set_wibtors_en(bool wibtors_en) {
      m_wibtors_en = wibtors_en;
      TLOG_DEBUG(1) << "Wibulator enable set to " << m_wibtors_en;
    }

    void DTPPodNode::set_outsink_en(bool outsink_en) {
      m_outsink_en = outsink_en;
      TLOG_DEBUG(1) << "Outsink enable set to " << m_outsink_en;
    }        

    int DTPPodNode::get_n_links() {
      return m_n_links;
    }

    int DTPPodNode::get_n_streams() {
      return m_n_streams;
    }

    int DTPPodNode::get_n_mux() {
      return m_n_mux;
    }

    int DTPPodNode::get_wibtors_width() {
      return m_wibtors_width;
    }

    int DTPPodNode::get_outsink_width() {
      return m_outsink_width;
    }

    bool DTPPodNode::get_wibtors_en() {
      return m_wibtors_en;
    }

    bool DTPPodNode::get_outsink_en() {
      return m_outsink_en;
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
    
    const LinkProcessorNode& DTPPodNode::get_link_processor_node(int i) const {
      if (i < m_n_links) {
	std::string name("linkproc");
	name += std::to_string(i);
	return getNode<LinkProcessorNode>(name);
      }
      else {
	//throw
      }
    }

    const WibulatorNode& DTPPodNode::get_wibulator_node(int i) const {
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
    
      auto ctrl_node = get_control_node();
      ctrl_node.soft_reset(true);
      ctrl_node.master_reset(true);	

      /*      for (uint i=0; i!=m_n_links; ++i) {	
	auto lDataReceptionNode = get_link_processor_node(i).get_data_router_node().get_data_reception_node();
	lDataReceptionNode.reset(true);
	} */

    }

    void DTPPodNode::reset_counters() const {

      

    }
    
    void DTPPodNode::set_threshold_all(int threshold) const {

      for (int i_link=0; i_link!=m_n_links; ++i_link) {
        for (int i_stream=0; i_stream!=m_n_streams; ++i_stream) {
	  
	  uint32_t il = static_cast<uint32_t>(i_link);
	  uint32_t is = static_cast<uint32_t>(i_stream);
          auto l_sa_node = get_link_processor_node(il).get_stream_proc_array_node();
          l_sa_node.stream_select(is, false);
          l_sa_node.get_stream_proc_node().set_threshold(threshold, false);
	  
        }
      }

      getClient().dispatch();

    }

    std::vector<MonProbeNodeInfo> DTPPodNode::get_mon_probe_info(int link, int stream) const {

      std::vector<MonProbeNodeInfo> tmp;

      auto l_sa_node = get_link_processor_node(link).get_stream_proc_array_node();

      // capture counters
      l_sa_node.getNode("csr.ctrl.cap_ctrs").write(0x1);
      l_sa_node.getNode("csr.ctrl.cap_ctrs").write(0x0);
      l_sa_node.getClient().dispatch();

      // select link
      l_sa_node.stream_select(stream, true);
      l_sa_node.getClient().dispatch();

      // loop over probes
      int n_probes = l_sa_node.get_stream_proc_node().get_n_probes();     
 
      for (int i_probe=0; i_probe!=n_probes; ++i_probe) {
	
	uint32_t ip = static_cast<uint32_t>(i_probe);
	MonProbeNodeInfo info = l_sa_node.get_stream_proc_node().get_mon_probe_node(ip).get_info();

	info.link = link;
	info.stream = stream;
	info.probe = i_probe;
	
	tmp.push_back(info);
      }
      
      return tmp;
      
    }

  } // namespace dtpcontrols
} // namespace dunedaq

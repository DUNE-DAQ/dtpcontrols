/**
 * @file DTPPodNode.hpp
 *
 * Top level DTP Pod
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_

// dtpcontrols Headers
#include "dtpcontrols/InfoNode.hpp"
#include "dtpcontrols/ControlNode.hpp"
#include "dtpcontrols/FlowMasterNode.hpp"
#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
#include "dtpcontrols/OutputSinkNode.hpp"
#include "dtpcontrols/WibulatorNode.hpp"
#include "dtpcontrols/LinkProcessorNode.hpp"
#include "dtpcontrols/MonProbeNodeInfo.hpp"


// uHal Headers
#include "uhal/DerivedNode.hpp"
#include "ers/Issue.hpp"

// C++ Headers
#include <chrono>
#include <map>
#include <string>

namespace dunedaq {
  namespace dtpcontrols {

    class DTPPodNode : public uhal::Node
    {

      UHAL_DERIVEDNODE(DTPPodNode)

      public:

      explicit DTPPodNode(const uhal::Node& node);
      virtual ~DTPPodNode();

      // set firmware build config information
      void set_n_links(int n_links);
      void set_n_port(int n_port);
      void set_n_mux(int n_mux);
      void set_wibtors_width(int wibtors_width);
      void set_outsink_width(int outsink_width);
      void set_wibtors_en(bool wibtors_en);
      void set_outsink_en(bool outsink_en);      

      int get_n_links();
      int get_n_streams();
      int get_n_mux();
      int get_wibtors_width();
      int get_outsink_width();
      bool get_wibtors_en();
      bool get_outsink_en();

      // get nodes
      const InfoNode& get_info_node() const;
      const ControlNode& get_control_node() const;
      const FlowMasterNode& get_flowmaster_node() const;
      const WibulatorNode& get_wibulator_node(int i) const;
      const LinkProcessorNode& get_link_processor_node(int i) const;
      const CentralRouterInterfaceNode& get_crif_node() const;
      const OutputSinkNode& get_output_sink_node() const;

      // reset everything
      void reset() const;

      // reset counters
      void reset_counters() const;

      // setup a link processor
      void setup_processor(int link, bool enable, bool drop_empty) const;

      // set all thresholds
      void set_threshold_all(int threshold) const;

      // reset all masks
      void reset_masks() const;

      // set masks for all channels in one link/pipe
      void set_channel_mask(int link, int pipe, uint64_t mask) const;

      // mask one channel
      void mask_channel(int link, int pipe, int channel) const;

      // enable CRIF
      void enable_crif() const;

      // disable CRIF
      void disable_crif() const;

      // get mon probe info
      std::vector<MonProbeNodeInfo> get_mon_probe_info(int link, int pipe) const;

    private:
      
      // firware config info this build contains
      std::map<std::string, uint32_t> m_dtp_fw_info;
      int m_n_links = 0;
      int m_n_streams = 0;
      int m_n_mux = 0;
      int m_wibtors_width = 0;
      int m_outsink_width = 0;
      bool m_wibtors_en = false;
      bool m_outsink_en = false;      
    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_

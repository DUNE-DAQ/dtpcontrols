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
      void set_n_links(uint32_t n_links);
      void set_n_port(uint32_t n_port);
      void set_n_mux(uint32_t n_mux);
      void set_wibtors_width(uint32_t wibtors_width);
      void set_outsink_width(uint32_t outsink_width);
      void set_wibtors_en(uint32_t wibtors_en);
      void set_outsink_en(uint32_t outsink_en);      
      // get nodes
      const InfoNode& get_info_node() const;
      const ControlNode& get_control_node() const;
      const FlowMasterNode& get_flowmaster_node() const;
      const WibulatorNode& get_wibulator_node(uint i) const;
      const LinkProcessorNode& get_link_processor_node(uint i) const;
      const CentralRouterInterfaceNode& get_crif_node() const;
      const OutputSinkNode& get_output_sink_node() const;

      // reset everything
      void reset() const;

      // configure TP generation
      // this is a placeholder - a configuration set will be needed as argument
      void configure() const;

      // enable TP generation
      void enable() const;

    private:
      
      // firware config info this build contains
      std::map<std::string, uint32_t> m_dtp_fw_info;
      uint32_t m_n_links = 0;
      uint32_t m_n_port = 0;
      uint32_t m_n_mux = 0;
      uint32_t m_wibtors_width = 0;
      uint32_t m_outsink_width = 0;
      uint32_t m_wibtors_en = false;
      uint32_t m_outsink_en = false;      
    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_

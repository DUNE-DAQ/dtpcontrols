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
#include <uhal/ValMem.hpp>

namespace dunedaq {
  namespace dtpcontrols {

    class DTPPodNode : public uhal::Node
    {

      UHAL_DERIVEDNODE(DTPPodNode)

      public:

      explicit DTPPodNode(const uhal::Node& node, uint n_links=5);
      virtual ~DTPPodNode();

      // get nodes
      const InfoNode& get_info_node() const;
      const ControlNode& get_control_node() const;
      const FlowMasterNode& get_flowmaster_node() const;
      const WibulatorNode& get_wibulator_node(uint i) const;
      const LinkProcessorNode& get_link_processor_node(uint i) const;
      const CentralRouterInterfaceNode& get_crif_node() const;
      const OutputSinkNode& get_output_sink_node() const;

      // read firmware config info
      std::map<std::string, uint32_t> get_firmware_config_info();
      // reset everything
      void reset();

      // configure TP generation
      // this is a placeholder - a configuration set will be needed as argument
      void configure();

      // enable TP generation
      void enable();

    private:
      
      // how many links does this build contain
      std::map<std::string, uint32_t> m_dtp_fw_info;
      uint32_t m_n_links;

    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_

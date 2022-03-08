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
      void configure();

      // enable TP generation
      void enable();

    private:
      
      // how many links does this build contain
      uint32_t m_n_links;

    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_DTPPODNODE_HPP_

/**
 * @file InfoNode.hpp
 *
 * InfoNode is a xample of uhal::Node derived class.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_INFONODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_INFONODE_HPP_

// dtpcontrols Headers

// uHal Headers
#include "uhal/DerivedNode.hpp"
#include "ers/Issue.hpp"

// C++ Headers

namespace dunedaq {
  namespace dtpcontrols {
    /**
     * @brief      Info firmware node
     */
    class InfoNode : public uhal::Node
    {

      UHAL_DERIVEDNODE(InfoNode)

      public:
      explicit InfoNode(const uhal::Node& node);
      virtual ~InfoNode();

      // read firmware config info
      std::map<std::string, uint32_t> get_firmware_config_info() const;
      
    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_INFONODE_HPP_

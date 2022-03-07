/**
 * @file WibulatorNode.hpp
 *
 * WibulatorNode is a xample of uhal::Node derived class.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

// dtpcontrols Headers

// uHal Headers
#include "uhal/DerivedNode.hpp"
#include "ers/Issue.hpp"

// C++ Headers


namespace dunedaq {
  namespace dtpcontrols {
    /**
     * @brief      Wibulator firmware node
     */
    class WibulatorNode : public uhal::Node
    {

      UHAL_DERIVEDNODE(WibulatorNode)

      public:
      explicit WibulatorNode(const uhal::Node& node);
      virtual ~WibulatorNode();

      void set_fire(bool);
      void set_max_word(const uint32_t&, const bool);
      void set_buffer_address(bool);
      void set_buffer_data(const std::vector<uint32_t>&, const bool);
      void set_chain(bool);  
      uhal::ValVector<uint32_t> get_buffer_data(const uint32_t&, const bool);
      uhal::ValWord<uint32_t> get_address_width(const bool);
      uhal::ValWord<uint32_t> get_max_word(const bool);

    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

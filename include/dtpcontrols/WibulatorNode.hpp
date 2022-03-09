/**
 * @file WibulatorNode.hpp
 *
 * WibulatorNode is a class derived from uhal::Node.
 * Its purpose is to control the wibulator component inside
 * DTP-firmware which is part of DUNE DAQ.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

// dtpcontrols Headers

// uhal headers

#include "uhal/DerivedNode.hpp"
#include "ers/Issue.hpp"

// C++ Headers

namespace dunedaq {
  namespace dtpcontrols {
    /**
     * @brief      Wibulator firmware node.
     */
    class WibulatorNode : public uhal::Node {

      UHAL_DERIVEDNODE(WibulatorNode)
      
      public:
      explicit WibulatorNode(const uhal::Node& );
      virtual ~WibulatorNode();
      void set_fire(bool);
      void set_max_word(const uint32_t&, bool);
      void set_buffer_address(bool);
      void set_buffer_data(const std::vector<uint32_t>&, bool);
      void set_chain(uint32_t, bool);  
      uhal::ValVector<uint32_t> get_buffer_data(const uint32_t&, bool);
      uhal::ValWord<uint32_t> get_address_width(bool);
      uhal::ValWord<uint32_t> get_max_word(bool);
      uhal::ValWord<uint32_t> get_size(void);      
    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

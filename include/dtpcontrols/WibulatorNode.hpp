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
#include "dtpcontrols/toolbox.hpp"
// uhal headers

#include "uhal/DerivedNode.hpp"
#include "ers/Issue.hpp"

// C++ Headers
#include <fstream>
#include <vector>

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
      std::vector<std::uint64_t> load_WIB_pattern_from_file(const std::string&);
      void write_pattern(std::vector<std::uint64_t>);
      std::vector<uint64_t> read_pattern();
      void fire();
      void set_fire(const uint32_t&, bool);
      uhal::ValWord<uint32_t> get_address_width(bool);
      uhal::ValWord<uint32_t> get_size(void);      
    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_WIBULATORNODE_HPP_

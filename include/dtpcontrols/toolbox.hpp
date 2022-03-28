/**
 * @file toolbox.hpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_TOOLBOX_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_TOOLBOX_HPP_

// uHal headers
#include "uhal/uhal.hpp"

// C++ headers
#include <string>

namespace dunedaq {
  namespace dtpcontrols {

    std::string find_connection_file();
    std::vector<std::uint32_t> format_36b_to_32b
    (const std::vector<std::uint64_t>& pattern_36b);
    std::vector<std::uint64_t> format_32b_to_36b
    (const uhal::ValVector<uint32_t>& pattern_32b);

  } // namespace dtp_controls
} // namespace dunedaq


#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_TOOLBOX_HPP_

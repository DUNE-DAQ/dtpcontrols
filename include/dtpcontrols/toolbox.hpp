
#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_TOOLBOX_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_TOOLBOX_HPP_

// uHal headers
#include "uhal/uhal.hpp"

// C++ headers
#include <string>
#include <map>
#include <uhal/ValMem.hpp>
#include <vector>

namespace dunedaq {
  namespace dtpcontrols {

    std::string find_connection_file();
    std::vector<std::uint32_t> format_36b_to_32b
    (const std::vector<std::uint64_t>&);
    std::vector<std::uint64_t> format_32b_to_36b
    (const uhal::ValVector<uint32_t>&);

  } // namespace dtp_controls
} // namespace dunedaq


#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_TOOLBOX_HPP_

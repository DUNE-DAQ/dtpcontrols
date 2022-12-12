/**
 * @file ExampleNode.hpp
 *
 * ExampleNode is a xample of uhal::Node derived class.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_EXAMPLENODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_EXAMPLENODE_HPP_

// dtpcontrols Headers

// uHal Headers
#include "ers/Issue.hpp"
#include "uhal/DerivedNode.hpp"

// C++ Headers
#include <chrono>
#include <map>
#include <string>

namespace dunedaq {
namespace dtpcontrols {
/**
 * @brief      Example of uhal::Node derived class.
 */
class ExampleNode : public uhal::Node
{

  UHAL_DERIVEDNODE(ExampleNode)

public:
  explicit ExampleNode(const uhal::Node& node);
  virtual ~ExampleNode();

  /**
   * @brief     Get the status string of the node. Optionally print it
   */
  virtual std::string get_status(bool print_out = false) const;

  /**
   * @brief     Read subnodes.
   */
  std::map<std::string, uhal::ValWord<uint32_t>> read_sub_nodes(const uhal::Node& node, // NOLINT(build/unsigned)
                                                                bool dispatch = true) const;

  /**
   * @brief     Reset subnodes.
   */
  void reset_sub_nodes(const uhal::Node& node,
                       uint32_t aValue = 0x0, // NOLINT(build/unsigned)
                       bool dispatch = true) const;
};

} // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_EXAMPLENODE_HPP_
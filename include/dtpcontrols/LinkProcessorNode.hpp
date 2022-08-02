/**
 * @file LinkProcessorNode.hpp
 *
 * LinkProcessorNode is a DTP firmware node which contains a DataRouterNode
 * and StreamProcessorArrayNode
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_LINKPROCESSORNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_LINKPROCESSORNODE_HPP_

// uHal Headers
#include "uhal/DerivedNode.hpp"

#include "dtpcontrols/DataRouterNode.hpp"
#include "dtpcontrols/StreamProcessorArrayNode.hpp"

namespace dunedaq {
namespace dtpcontrols {

class LinkProcessorNode : public uhal::Node {

  UHAL_DERIVEDNODE(LinkProcessorNode)

public:
  explicit LinkProcessorNode(const uhal::Node& node);
  ~LinkProcessorNode();

  const DataRouterNode& get_data_router_node() const;
  const StreamProcessorArrayNode& get_stream_proc_array_node() const;

  // setup all processors
  void setup(bool enable, bool drop_empty) const;

  // convenience methods for accessing stream processors
  void set_threshold(int stream, uint32_t threshold) const;
  uint32_t get_threshold(int stream) const;

  void set_channel_mask(int stream, uint32_t channel, uint32_t mask) const;
  uint32_t get_channel_mask(int stream, uint32_t channel) const;

  void set_channel_mask_all(int stream, uint64_t mask) const;
  uint64_t get_channel_mask_all(int stream) const;

private:
  int m_n_streams;

};



} // namespace dtpcontrols
} // namespace dunedaq


#endif //DTPCONTROLS_INCLUDE_DTPCONTROLS_LINKPROCESSORNODE_HPP_

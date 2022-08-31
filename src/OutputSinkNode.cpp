/**
 * @file OutputSinkNode.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/OutputSinkNode.hpp"

#include "logging/Logging.hpp"

#include <map>
#include <string>

namespace dunedaq {
  namespace dtpcontrols {

    UHAL_REGISTER_DERIVED_NODE(OutputSinkNode)

 //-----------------------------------------------------------------------------
    OutputSinkNode::OutputSinkNode(const uhal::Node& node)
    : uhal::Node(node)
    {}
//-----------------------------------------------------------------------------

 //-----------------------------------------------------------------------------
    OutputSinkNode::~OutputSinkNode() {}
 //-----------------------------------------------------------------------------

    void OutputSinkNode::enable(bool dispatch) const {
      getNode("csr.ctrl.en").write(0x1);
      if(dispatch) {getClient().dispatch();}
    }
 //-----------------------------------------------------------------------------
    void OutputSinkNode::disable(bool dispatch) const {
      getNode("csr.ctrl.en").write(0x0);
      if(dispatch) {getClient().dispatch();}
    }
 //-----------------------------------------------------------------------------
    void OutputSinkNode::clear(bool dispatch) const {
      getNode("csr.ctrl.clear").write(0x1);
      getNode("csr.ctrl.clear").write(0x0);
      if(dispatch) {getClient().dispatch();}
    }
 //-----------------------------------------------------------------------------
    void OutputSinkNode::drop_idles(bool dispatch) const {
      getNode("csr.pattern_kchar").write(0x1);
      getNode("csr.pattern_data").write(0xbc);
      getNode("csr.pattern_filter").write(0x1);
      if(dispatch) {getClient().dispatch();}
    }
 //-----------------------------------------------------------------------------
    void OutputSinkNode::keep_idles(bool dispatch) const {
      getNode("csr.pattern_kchar").write(0x0);
      getNode("csr.pattern_data").write(0x0);
      getNode("csr.pattern_filter").write(0x0);
      if(dispatch) {getClient().dispatch();}
    }
 //-----------------------------------------------------------------------------

  } // namespace dtpcontrols
} // namespace dunedaq

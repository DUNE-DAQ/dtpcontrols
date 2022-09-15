/**
 * @file StreamProcessorNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <pybind11/pybind11.h>

#include "dtpcontrols/StreamProcessorNode.hpp"

namespace py = pybind11;
using namespace pybind11::literals; 

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_stream_processor_node(py::module &m) {
  py::class_<StreamProcessorNode, uhal::Node>(
      m, "StreamProcessorNode")
      .def(py::init<const uhal::Node &>())
      .def("drop_empty", &StreamProcessorNode::drop_empty, "dispatch"_a = true)
      .def("set_threshold", &StreamProcessorNode::set_threshold, "threshold"_a, "dispatch"_a = true)
      .def("set_channel_mask_all", &StreamProcessorNode::set_channel_mask_all, "mask"_a, "dispatch"_a = true)
      .def("get_channel_mask_all", &StreamProcessorNode::set_channel_mask_all)
      .def("capture_pedestal", &StreamProcessorNode::capture_pedestal, "enable"_a, "dispatch"_a = true);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

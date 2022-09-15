/**
 * @file LinkProcessorNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <pybind11/pybind11.h>

#include "dtpcontrols/LinkProcessorNode.hpp"

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_link_processor_node(py::module& m) {

  py::class_<dtpcontrols::LinkProcessorNode, uhal::Node>(m, "LinkProcessorNode")
      .def(py::init<const uhal::Node&>())
      .def("get_data_router_node", &dtpcontrols::LinkProcessorNode::get_data_router_node)
      .def("get_stream_proc_array_node", &dtpcontrols::LinkProcessorNode::get_stream_proc_array_node);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

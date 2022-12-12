/**
 * @file OutputSinkNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols_wrapper.hpp"
#include "dtpcontrols/OutputSinkNode.hpp"

namespace py = pybind11;
using namespace pybind11::literals;
namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_output_sink_node(py::module& m) {
  py::class_<dtpcontrols::OutputSinkNode, uhal::Node>(m, "OutputSinkNode")
      .def(py::init<const uhal::Node&>())
      .def("enable", &dtpcontrols::OutputSinkNode::enable, "dispatch"_a = true)
      .def("disable", &dtpcontrols::OutputSinkNode::disable, "dispatch"_a = true)
      .def("clear", &dtpcontrols::OutputSinkNode::clear, "dispatch"_a = true)
      .def("drop_idles", &dtpcontrols::OutputSinkNode::drop_idles, "dispatch"_a = true)
      .def("keep_idles", &dtpcontrols::OutputSinkNode::keep_idles, "dispatch"_a = true);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

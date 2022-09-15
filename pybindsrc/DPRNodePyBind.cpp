/**
 * @file DPRNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "dtpcontrols/DPRNode.hpp"

namespace py = pybind11;
using namespace pybind11::literals; 

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_dpr_node(py::module& m) {

  py::class_<dtpcontrols::DPRNode, uhal::Node>(m, "DPRNode")
      .def(py::init<const uhal::Node&>())
      .def("set_mux_in", &dtpcontrols::DPRNode::set_mux_in, "mux_in_choice"_a, "dispatch"_a = true)
      .def("set_mux_out", &dtpcontrols::DPRNode::set_mux_out, "mux_out_choice"_a, "dispatch"_a = true);
}
}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

/**
 * @file ControlNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/ControlNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_control_node(py::module& m){ 

    m.doc() = "c++ implementation of dtpcontrols Control python modules"; // optional module docstring

     py::class_<dtpcontrols::ControlNode, uhal::Node>(m, "ControlNode")
       .def(py::init<const uhal::Node&>())
       .def("SoftReset", &dtpcontrols::ControlNode::SoftReset, py::arg("dispatch") = true)
       .def("MasterReset", &dtpcontrols::ControlNode::MasterReset, py::arg("dispatch") = true)
       .def("Nuke", &dtpcontrols::ControlNode::Nuke, py::arg("dispatch") = true);
}

} // namespace python
} // namespace timing
} // namespace dunedaq

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

void register_control_node(py::module& m) {

  py::class_<dtpcontrols::ControlNode, uhal::Node>(m, "ControlNode")
      .def(py::init<const uhal::Node&>())
      .def("soft_reset", &dtpcontrols::ControlNode::soft_reset, py::arg("dispatch") = true)
      .def("master_reset", &dtpcontrols::ControlNode::master_reset, py::arg("dispatch") = true)
      .def("nuke", &dtpcontrols::ControlNode::nuke, py::arg("dispatch") = true);
      }

    } // namespace python
    }  // namespace dtpcontrols
} // namespace dunedaq

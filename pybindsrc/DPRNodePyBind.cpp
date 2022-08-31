/**
 * @file DPRNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DPRNode.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_dpr_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols DPR python modules"; // optional module docstring

	py::class_<dtpcontrols::DPRNode, uhal::Node>(m, "DPRNode")
	  .def(py::init<const uhal::Node&>())
	  .def("set_mux_in", &dtpcontrols::DPRNode::set_mux_in, py::arg("mux_in_choice"),
	       py::arg("dispatch") = true)
	  .def("set_mux_out", &dtpcontrols::DPRNode::set_mux_out, py::arg("mux_out_choice"),
	       py::arg("dispatch") = true);
      }
    } // namespace python
  } // namespace timing
} // namespace dunedaq

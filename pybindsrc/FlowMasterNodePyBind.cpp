/**
 * @file FlowMasterNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/FlowMasterNode.hpp"

#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>


namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_flowmaster_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols FlowMaster python modules"; // optional module docstring

	py::class_<dtpcontrols::FlowMasterNode, uhal::Node>(m, "FlowMasterNode")
	  .def(py::init<const uhal::Node&>())
	  .def("set_source_gbt", &dtpcontrols::FlowMasterNode::set_source_gbt,
	       py::arg("dispatch") = true)
	  .def("set_source_wtor", &dtpcontrols::FlowMasterNode::set_source_wtor,
	       py::arg("dispatch") = true)
	  .def("set_sink_hits", &dtpcontrols::FlowMasterNode::set_sink_hits,
	       py::arg("dispatch") = true)
	  .def("set_sink_link", &dtpcontrols::FlowMasterNode::set_sink_link,
	       py::arg("link"), py::arg("dispatch") = true)
	  .def("set_outflow", &dtpcontrols::FlowMasterNode::set_outflow,
	  	   py::arg("enable"), py::arg("dispatch") = true);
      }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

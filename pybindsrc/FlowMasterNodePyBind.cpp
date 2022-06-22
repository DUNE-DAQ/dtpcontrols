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
	  .def("source_select_gbt", &dtpcontrols::FlowMasterNode::select_source_gbt,
	       py::arg("dispatch") = true)
	  .def("source_select_wtor", &dtpcontrols::FlowMasterNode::select_source_wtor,
	       py::arg("dispatch") = true)
	  .def("source_select", py::overload_cast<const std::string&, const bool>(&FlowMasterNode::source_select),
	       py::arg("source"), py::arg("dispatch") = true)
	  .def("sink_select", py::overload_cast<const std::string&, const bool>(&FlowMasterNode::sink_select),
	       py::arg("sink"), py::arg("dispatch") = true);
      }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

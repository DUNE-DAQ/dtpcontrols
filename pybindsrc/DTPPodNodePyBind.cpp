/**
 * @file DTPPodNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DTPPodNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_dtppod_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols DTPPod python modules"; // optional module docstring

	py::class_<dtpcontrols::DTPPodNode, uhal::Node>(m, "DTPPodNode")
	  .def(py::init<const uhal::Node&>())
	  .def("get_info_node", &dtpcontrols::DTPPodNode::get_info_node)
	  .def("get_control_node", &dtpcontrols::DTPPodNode::get_control_node)
	  .def("get_flowmaster_node", &dtpcontrols::DTPPodNode::get_flowmaster_node)
	  .def("get_wibulator_node", &dtpcontrols::DTPPodNode::get_wibulator_node, py::arg("i"))
	  .def("get_link_processor_node", &dtpcontrols::DTPPodNode::get_link_processor_node, py::arg("i"))
	  .def("get_crif_node", &dtpcontrols::DTPPodNode::get_crif_node)
	  .def("get_output_sink_node", &dtpcontrols::DTPPodNode::get_output_sink_node)
	  .def("reset", &dtpcontrols::DTPPodNode::reset);
      }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

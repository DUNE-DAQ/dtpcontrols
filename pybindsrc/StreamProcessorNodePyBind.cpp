/**
 * @file StreamProcessorNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/StreamProcessorNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_stream_processor_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols StreamProcessor python modules"; // optional module docstring

	py::class_<dtpcontrols::StreamProcessorNode, uhal::Node>(m, "StreamProcessorNode")
	  .def(py::init<const uhal::Node &>())
	  .def("set_threshold", &dtpcontrols::StreamProcessorNode::set_threshold,
	       py::arg("threshold"), py::arg("dispatch") = true)
	  .def("set_channel_mask_all",
	       &dtpcontrols::StreamProcessorNode::set_channel_mask_all,
	       py::arg("mask"), py::arg("dispatch") = true)
	  .def("get_channel_mask_all",
	       &dtpcontrols::StreamProcessorNode::set_channel_mask_all);	
      }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

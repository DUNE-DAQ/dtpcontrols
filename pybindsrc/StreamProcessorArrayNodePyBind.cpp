/**
 * @file StreamProcessorArrayNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/StreamProcessorArrayNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_stream_processor_array_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols StreamProcessorArray python modules"; // optional module docstring

	py::class_<dtpcontrols::StreamProcessorArrayNode, uhal::Node>(m, "StreamProcessorArrayNode")
	  .def(py::init<const uhal::Node &>())
	  .def("stream_select",
	       &dtpcontrols::StreamProcessorArrayNode::stream_select,
	       py::arg("pipe"), py::arg("dispatch") = true)
	  .def("get_stream_proc_node",
	       &dtpcontrols::StreamProcessorArrayNode::get_stream_proc_node);
	
      }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

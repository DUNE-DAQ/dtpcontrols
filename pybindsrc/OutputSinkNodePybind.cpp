/**
 * @file OutputSinkNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/OutputSinkNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_output_sink_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols Output Sink python modules"; // optional module docstring

	py::class_<dtpcontrols::OutputSinkNode, uhal::Node>(m, "OutputSinkNode")
	  .def(py::init<const uhal::Node&>());
      }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

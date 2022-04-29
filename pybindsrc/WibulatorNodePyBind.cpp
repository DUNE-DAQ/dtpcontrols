/**
 * @file WibulatorNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/WibulatorNode.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_wibulator_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols Wibulator python modules"; // optional module docstring

	py::class_<dtpcontrols::WibulatorNode, uhal::Node>(m, "WibulatorNode")
	  .def(py::init<const uhal::Node&>())
	  .def("load_WIB_pattern_from_file", &dtpcontrols::WibulatorNode::load_WIB_pattern_from_file,
	       py::arg("path"))
	  .def("write_pattern", &dtpcontrols::WibulatorNode::write_pattern, py::arg("pattern"))
	  .def("read_pattern", &dtpcontrols::WibulatorNode::read_pattern)
	  .def("fire", &dtpcontrols::WibulatorNode::fire)
	  .def("get_size", &dtpcontrols::WibulatorNode::get_size);	  
      }
    } // namespace python
  } // namespace timing
} // namespace dunedaq

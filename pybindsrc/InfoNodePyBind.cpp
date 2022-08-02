/**
 * @file InfoNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/InfoNode.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_info_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols InfoNode python modules"; // optional module docstring

	py::class_<dtpcontrols::InfoNode, uhal::Node>(m, "InfoNode")
	  .def(py::init<const uhal::Node&>())
	  .def("get_firmware_config_info", &dtpcontrols::InfoNode::get_firmware_config_info);
      }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

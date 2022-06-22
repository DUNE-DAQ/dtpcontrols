
/**
 * @file toolboxPyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/toolbox.hpp"

#include <pybind11/cast.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_toolbox(py::module& m){

	m.doc() = "c++ implementation of dtpcontrols toolbox python modules"; // optional module docstring

	m.def("find_connection_file", &dtpcontrols::find_connection_file);
	m.def("format_36b_to_32b", &dtpcontrols::format_36b_to_32b, py::arg("pattern_36b"));
	m.def("format_32b_to_36b", &dtpcontrols::format_32b_to_36b, py::arg("pattern_32b"));
	m.def("get_child_registers", &dtpcontrols::get_child_registers, py::arg("node"));
	m.def("load_WIB_pattern_from_file", &dtpcontrols::load_WIB_pattern_from_file, py::arg("path"));
        }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

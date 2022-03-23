/**
 * @file dtpcontrols_wrapper.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */
#include "dtpcontrols/ExampleNode.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {
	
PYBIND11_MODULE(_daq_dtpcontrols_py, top_module) {

    top_module.doc() = "c++ implementation of dtpcontrols python modules"; // optional module docstring

     py::class_<dtpcontrols::ExampleNode, uhal::Node>(top_module, "ExampleNode")
    .def(py::init<const uhal::Node&>())
    .def("get_status", &dtpcontrols::ExampleNode::get_status);
}

} // namespace python
} // namespace dtpcontrols
} // namespace dunedaq

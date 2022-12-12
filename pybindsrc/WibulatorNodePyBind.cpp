/**
 * @file WibulatorNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols_wrapper.hpp"
#include <pybind11/stl.h>

#include "dtpcontrols/WibulatorNode.hpp"

namespace py = pybind11;
using namespace pybind11::literals; 

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_wibulator_node(py::module& m) {
  py::class_<dtpcontrols::WibulatorNode, uhal::Node>(m, "WibulatorNode")
      .def(py::init<const uhal::Node&>())
      .def("write_pattern", &dtpcontrols::WibulatorNode::write_pattern, "pattern"_a)
      .def("read_pattern", &dtpcontrols::WibulatorNode::read_pattern)
      .def("fire", &dtpcontrols::WibulatorNode::fire)
      .def("get_size", &dtpcontrols::WibulatorNode::get_size);
}
}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

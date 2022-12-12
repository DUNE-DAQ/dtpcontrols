/**
 * @file InfoNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols_wrapper.hpp"
#include <pybind11/stl.h>

#include "dtpcontrols/InfoNode.hpp"

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_info_node(py::module& m) {

  py::class_<dtpcontrols::InfoNode, uhal::Node>(m, "InfoNode")
      .def(py::init<const uhal::Node&>())
      .def("get_firmware_config_info", &dtpcontrols::InfoNode::get_firmware_config_info)
      .def("get_firmware_id_info", &dtpcontrols::InfoNode::get_firmware_id_info);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

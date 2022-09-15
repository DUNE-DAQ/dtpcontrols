/**
 * @file DTPPodNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <pybind11/pybind11.h>

#include "dtpcontrols/DTPPodController.hpp"

namespace py = pybind11;
using namespace pybind11::literals; 

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_dtppodcontroller(py::module& m) {

  py::class_<DTPPodController>(m, "DTPPodController")
      .def(py::init<uhal::HwInterface>())
      .def("get_node", &DTPPodController::get_node, py::return_value_policy::reference_internal)
      .def("get_info_node", &DTPPodController::get_info_node, py::return_value_policy::reference_internal)
      .def("get_control_node", &DTPPodController::get_control_node, py::return_value_policy::reference_internal)
      .def("get_flowmaster_node", &DTPPodController::get_flowmaster_node, py::return_value_policy::reference_internal)
      .def("get_wibulator_node", &DTPPodController::get_wibulator_node, "i"_a, py::return_value_policy::reference_internal)
      .def("get_link_processor_node", &DTPPodController::get_link_processor_node, "i"_a, py::return_value_policy::reference_internal)
      .def("get_crif_node", &DTPPodController::get_crif_node, py::return_value_policy::reference_internal)
      .def("get_output_sink_node", &DTPPodController::get_output_sink_node, py::return_value_policy::reference_internal)
      .def("reset", &DTPPodController::reset);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

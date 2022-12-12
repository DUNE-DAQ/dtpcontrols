/**
 * @file dtpcontrols_wrapper.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols_wrapper.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

PYBIND11_MAKE_OPAQUE(std::vector<int>)

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

extern void register_central_router_interface_node(py::module&);
extern void register_control_node(py::module& m);
extern void register_data_reception_node(py::module& m);
extern void register_flowmaster_node(py::module& m);
extern void register_stream_processor_array_node(py::module& m);
extern void register_stream_processor_node(py::module& m);
extern void register_wibulator_node(py::module& m);
extern void register_link_processor_node(py::module& m);
extern void register_toolbox(py::module& m);
extern void register_info_node(py::module& m);
extern void register_data_router_node(py::module& m);
extern void register_dpr_node(py::module& m);
extern void register_output_sink_node(py::module& m);

extern void register_dtppodcontroller(py::module& m);

PYBIND11_MODULE(_daq_dtpcontrols_py, top_module) {
  top_module.doc() =
      "c++ implementation of dtpcontrols python modules";  // optional module
                                                           // docstring

  py::module_ core_module = top_module.def_submodule("core");

  dtpcontrols::python::register_central_router_interface_node(core_module);
  dtpcontrols::python::register_control_node(core_module);
  dtpcontrols::python::register_data_reception_node(core_module);
  dtpcontrols::python::register_flowmaster_node(core_module);
  dtpcontrols::python::register_stream_processor_array_node(core_module);
  dtpcontrols::python::register_stream_processor_node(core_module);
  dtpcontrols::python::register_wibulator_node(core_module);
  dtpcontrols::python::register_link_processor_node(core_module);
  dtpcontrols::python::register_toolbox(core_module);
  dtpcontrols::python::register_info_node(core_module);
  dtpcontrols::python::register_data_router_node(core_module);
  dtpcontrols::python::register_dpr_node(core_module);
  dtpcontrols::python::register_output_sink_node(core_module);

  dtpcontrols::python::register_dtppodcontroller(core_module);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

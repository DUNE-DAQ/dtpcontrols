/**
 * @file dtpcontrols_wrapper.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef __DTPCONTROLS_PYBINDSRC_DTP_CONTROLS_WRAPPER__
#define __DTPCONTROLS_PYBINDSRC_DTP_CONTROLS_WRAPPER__

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void
register_central_router_interface_node(py::module&);
void
register_control_node(py::module& m);
void
register_data_reception_node(py::module& m);
void
register_flowmaster_node(py::module& m);
void
register_stream_processor_array_node(py::module& m);
void
register_stream_processor_node(py::module& m);
void
register_wibulator_node(py::module& m);
void
register_link_processor_node(py::module& m);
void
register_toolbox(py::module& m);
void
register_info_node(py::module& m);
void
register_data_router_node(py::module& m);
void
register_dpr_node(py::module& m);
void
register_output_sink_node(py::module& m);

void
register_dtppodcontroller(py::module& m);

} // namespace python
} // namespace dtpcontrols
} // namespace dunedaq

#endif /* __DTPCONTROLS_PYBINDSRC_DTP_CONTROLS_WRAPPER__ */

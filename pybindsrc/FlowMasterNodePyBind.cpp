/**
 * @file FlowMasterNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols_wrapper.hpp"
#include <pybind11/detail/common.h>

#include "dtpcontrols/FlowMasterNode.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void
register_flowmaster_node(py::module& m)
{

  py::class_<FlowMasterNode, uhal::Node>(m, "FlowMasterNode")
    .def(py::init<const uhal::Node&>())
    .def("set_source_gbt", &FlowMasterNode::set_source_gbt, "dispatch"_a = true)
    .def("set_source_wtor", &FlowMasterNode::set_source_wtor, "dispatch"_a = true)
    .def("set_sink_hits", &FlowMasterNode::set_sink_hits, "dispatch"_a = true)
    .def("set_sink_link", &FlowMasterNode::set_sink_link, "link"_a, "dispatch"_a = true)
    .def("set_outflow", &FlowMasterNode::set_outflow, "mode"_a, "dispatch"_a = true);
}

} // namespace python
} // namespace dtpcontrols
} // namespace dunedaq

/**
 * @file CentralRouterInterfaceNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/CentralRouterInterfaceNode.hpp"
#include "dtpcontrols_wrapper.hpp"

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void
register_central_router_interface_node(py::module& m)
{

  py::class_<dtpcontrols::CentralRouterInterfaceNode, uhal::Node>(m, "CentralRouterInterfaceNode")
    .def(py::init<const uhal::Node&>())
    .def("enable", &dtpcontrols::CentralRouterInterfaceNode::enable, py::arg("dispatch") = true)
    .def("set_drop_empty", &dtpcontrols::CentralRouterInterfaceNode::set_drop_empty, py::arg("dispatch") = true)
    .def("get_drop_empty", &dtpcontrols::CentralRouterInterfaceNode::set_drop_empty, py::arg("dispatch") = true);
}

} // namespace python
} // namespace dtpcontrols
} // namespace dunedaq

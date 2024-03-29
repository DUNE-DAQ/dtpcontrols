/**
 * @file DataRouterNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols_wrapper.hpp"
#include "dtpcontrols/DataRouterNode.hpp"

namespace py = pybind11;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_data_router_node(py::module& m) {
  py::class_<dtpcontrols::DataRouterNode, uhal::Node>(m, "DataRouterNode")
      .def(py::init<const uhal::Node&>())
      .def("get_data_reception_node", &dtpcontrols::DataRouterNode::get_data_reception_node)
      .def("get_dpr_node", &dtpcontrols::DataRouterNode::get_dpr_node);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

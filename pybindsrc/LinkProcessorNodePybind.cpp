/**
 * @file LinkProcessorNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols_wrapper.hpp"
#include "dtpcontrols/LinkProcessorNode.hpp"

namespace py = pybind11;
using namespace pybind11::literals; 

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_link_processor_node(py::module& m) {

  py::class_<LinkProcessorNode, uhal::Node>(m, "LinkProcessorNode")
      .def(py::init<const uhal::Node&>())
      .def("setup_dr", &LinkProcessorNode::setup_dr, "enable"_a = true)
      .def("drop_empty", &LinkProcessorNode::drop_empty, "drop"_a = true)

      .def("get_threshold", &LinkProcessorNode::get_threshold)
      .def("get_channel_mask", &LinkProcessorNode::get_channel_mask)
      .def("get_channel_mask_all", &LinkProcessorNode::get_channel_mask_all)
      
      .def("set_threshold", &LinkProcessorNode::set_threshold)
      .def("set_channel_mask", &LinkProcessorNode::set_channel_mask)
      .def("set_channel_mask_all", &LinkProcessorNode::set_channel_mask_all)
      
      .def("capture_pedestal", &LinkProcessorNode::capture_pedestal)
      
      .def("get_data_router_node", &LinkProcessorNode::get_data_router_node)
      .def("get_stream_proc_array_node", &LinkProcessorNode::get_stream_proc_array_node)
      .def("get_central_router_node", &LinkProcessorNode::get_central_router_node, "i"_a, py::return_value_policy::reference_internal);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

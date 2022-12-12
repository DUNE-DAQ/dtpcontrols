/**
 * @file StreamProcessorArrayNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/StreamProcessorArrayNode.hpp"
#include "dtpcontrols_wrapper.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void
register_stream_processor_array_node(py::module& m)
{
  py::class_<StreamProcessorArrayNode, uhal::Node>(m, "StreamProcessorArrayNode")
    .def(py::init<const uhal::Node&>())
    .def("stream_select", &StreamProcessorArrayNode::stream_select, "pipe"_a, "dispatch"_a = true)
    .def("get_stream_proc_node", &StreamProcessorArrayNode::get_stream_proc_node);
}

} // namespace python
} // namespace dtpcontrols
} // namespace dunedaq

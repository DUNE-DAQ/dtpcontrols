/**
 * @file DataReceptionNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include <pybind11/pybind11.h>

#include "dtpcontrols/DataReceptionNode.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void register_data_reception_node(py::module& m) {
  py::class_<dtpcontrols::DataReceptionNode, uhal::Node>(m, "DataReceptionNode")
      .def(py::init<const uhal::Node&>())
      .def("enable", &dtpcontrols::DataReceptionNode::enable, "dispatch"_a = true)
      .def("reset_input_word_counter", &dtpcontrols::DataReceptionNode::reset_input_word_counter,  "dispatch"_a = true)
      .def("reset_output_word_counter", &dtpcontrols::DataReceptionNode::reset_output_word_counter, "dispatch"_a = true)
      .def("error_reset", &dtpcontrols::DataReceptionNode::error_reset, "dispatch"_a = true)
      .def("reset", &dtpcontrols::DataReceptionNode::reset, "dispatch"_a = true);
}

}  // namespace python
}  // namespace dtpcontrols
}  // namespace dunedaq

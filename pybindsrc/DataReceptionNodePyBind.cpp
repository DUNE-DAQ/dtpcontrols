/**
 * @file DataReceptionNodePyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols/DataReceptionNode.hpp"

#include <pybind11/pybind11.h>

namespace py = pybind11;

namespace dunedaq {
  namespace dtpcontrols {
    namespace python {

      void register_data_reception_node(py::module& m){ 

	m.doc() = "c++ implementation of dtpcontrols DataReception python modules"; // optional module docstring

	py::class_<dtpcontrols::DataReceptionNode, uhal::Node>(m, "DataReceptionNode")
	  .def(py::init<const uhal::Node&>())
	  .def("enable", &dtpcontrols::DataReceptionNode::enable, py::arg("dispatch") = true)
	  .def("reset_input_word_counter", &dtpcontrols::DataReceptionNode::reset_input_word_counter,
	       py::arg("dispatch") = true)
	  .def("reset_output_word_counter", &dtpcontrols::DataReceptionNode::reset_output_word_counter,
	       py::arg("dispatch") = true)
	  .def("error_reset", &dtpcontrols::DataReceptionNode::error_reset, py::arg("dispatch") = true)
	  .def("reset", &dtpcontrols::DataReceptionNode::reset, py::arg("dispatch") = true);
      }

    } // namespace python
  } // namespace timing
} // namespace dunedaq

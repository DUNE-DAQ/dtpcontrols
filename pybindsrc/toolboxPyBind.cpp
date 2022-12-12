
/**
 * @file toolboxPyBind.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "dtpcontrols_wrapper.hpp"
#include <pybind11/cast.h>
#include <pybind11/stl.h>

#include "dtpcontrols/toolbox.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

namespace dunedaq {
namespace dtpcontrols {
namespace python {

void
register_toolbox(py::module& m)
{
  m.def("find_connection_file", &dtpcontrols::find_connection_file);
  m.def("format_36b_to_32b", &dtpcontrols::format_36b_to_32b, "pattern_36b"_a);
  m.def("format_32b_to_36b", &dtpcontrols::format_32b_to_36b, "pattern_32b"_a);
  m.def("read_WIB_pattern_from_file", &dtpcontrols::read_WIB_pattern_from_file, "path"_a);
  m.def("get_child_registers", &dtpcontrols::get_child_registers, "node"_a);
}

} // namespace python
} // namespace dtpcontrols
} // namespace dunedaq

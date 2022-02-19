cmake_minimum_required(VERSION 3.12)
project(dtpcontrols VERSION 0.0.1)

find_package(daq-cmake REQUIRED)

daq_setup_environment()

find_package(ers REQUIRED)     
find_package(logging REQUIRED)
find_package(pybind11 REQUIRED)
find_package(uhal REQUIRED)

##############################################################################
daq_add_library(*.cpp LINK_LIBRARIES ers::ers logging::logging uhal::uhal)

##############################################################################
daq_add_python_bindings(*.cpp LINK_LIBRARIES ${PROJECT_NAME})

##############################################################################
daq_install()

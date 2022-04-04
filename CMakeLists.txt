cmake_minimum_required(VERSION 3.12)

project(dtpcontrols VERSION 2.0.0)

find_package(daq-cmake REQUIRED)

daq_setup_environment()

find_package(ers REQUIRED)     
find_package(logging REQUIRED)
find_package(pybind11 REQUIRED)
find_package(uhal REQUIRED)
find_package(uhallibs REQUIRED)

##############################################################################
daq_add_library(*.cpp LINK_LIBRARIES ers::ers logging::logging uhal::uhal)

##############################################################################
#daq_add_python_bindings(*.cpp LINK_LIBRARIES ${PROJECT_NAME})

##############################################################################
# Integration tests
daq_add_application(dtpcontrols_test_nodes test_nodes.cxx TEST LINK_LIBRARIES uhal::uhal uhallibs::uhallibs dtpcontrols)
daq_add_application(dtpcontrols_test_reset test_reset.cxx TEST LINK_LIBRARIES uhal::uhal uhallibs::uhallibs dtpcontrols)
daq_add_application(dtpcontrols_test_config test_config.cxx TEST LINK_LIBRARIES uhal::uhal uhallibs::uhallibs dtpcontrols)
daq_add_application(dtpcontrols_test_enable test_enable.cxx TEST LINK_LIBRARIES uhal::uhal uhallibs::uhallibs dtpcontrols)


##############################################################################
daq_install()

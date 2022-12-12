/**
 * @file MonProbeNodeInfo.hpp
 *
 * MonProbeNodeInfo is struct which stores data read from a MonProbeNode
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODEINFO_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODEINFO_HPP_

struct MonProbeNodeInfo
{

  int link;
  int stream;
  int probe;
  int ready;
  int valid;
  int user;
  int last;
  int last_err;
  int pkt_ctr;
  int axi_err;
};

#endif //  DTPCONTROLS_INCLUDE_DTPCONTROLS_MONPROBENODEINFO_HPP_

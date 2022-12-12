/**
 * @file OutputSinkNode.hpp
 *
 * OutputSinkNode is a xample of uhal::Node derived class.
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef DTPCONTROLS_INCLUDE_DTPCONTROLS_OUTPUTSINKNODE_HPP_
#define DTPCONTROLS_INCLUDE_DTPCONTROLS_OUTPUTSINKNODE_HPP_

// dtpcontrols Headers

// uHal Headers
#include "uhal/DerivedNode.hpp"
#include "ers/Issue.hpp"

// C++ Headers


namespace dunedaq {
  namespace dtpcontrols {
    /**
     * @brief      OutputSink firmware node
     */
    class OutputSinkNode : public uhal::Node
    {

      UHAL_DERIVEDNODE(OutputSinkNode)

      public:
      explicit OutputSinkNode(const uhal::Node& node);
      virtual ~OutputSinkNode();

      void enable(bool dispatch) const;
      void disable(bool dispatch) const;
      void clear(bool dispatch) const;
      void drop_idles(bool dispatch) const;
      void keep_idles(bool dispatch) const;      
    };

  } // namespace dtpcontrols
} // namespace dunedaq

#endif // DTPCONTROLS_INCLUDE_DTPCONTROLS_OUTPUTSINKNODE_HPP_

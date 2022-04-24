// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vysyx_22041207_top.h for the primary calling header

#ifndef VERILATED_VYSYX_22041207_TOP___024ROOT_H_
#define VERILATED_VYSYX_22041207_TOP___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vysyx_22041207_top__Syms;
class Vysyx_22041207_top_VerilatedVcd;


//----------

VL_MODULE(Vysyx_22041207_top___024root) {
  public:

    // PORTS
    VL_IN(inst,31,0);
    VL_OUT(pc,31,0);

    // INTERNAL VARIABLES
    Vysyx_22041207_top__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vysyx_22041207_top___024root);  ///< Copying not allowed
  public:
    Vysyx_22041207_top___024root(const char* name);
    ~Vysyx_22041207_top___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vysyx_22041207_top__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard

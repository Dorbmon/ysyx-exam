// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vtop__Syms;
class Vtop_VerilatedVcd;


//----------

VL_MODULE(Vtop___024root) {
  public:

    // PORTS
    VL_IN8(clk,0,0);
    VL_IN8(clrn,0,0);
    VL_IN8(ps2_clk,0,0);
    VL_IN8(ps2_data,0,0);
    VL_OUT8(HEX0,6,0);
    VL_OUT8(HEX1,6,0);
    VL_OUT8(HEX2,6,0);

    // LOCAL SIGNALS
    CData/*0:0*/ top__DOT__nextdata_n;
    CData/*0:0*/ top__DOT__overflow;
    CData/*0:0*/ top__DOT__ready;
    CData/*7:0*/ top__DOT__s0;
    CData/*7:0*/ top__DOT__s1;
    CData/*2:0*/ top__DOT__keyboard__DOT__w_ptr;
    CData/*2:0*/ top__DOT__keyboard__DOT__r_ptr;
    CData/*3:0*/ top__DOT__keyboard__DOT__count;
    CData/*2:0*/ top__DOT__keyboard__DOT__ps2_clk_sync;
    SData/*9:0*/ top__DOT__keyboard__DOT__buffer;
    VlUnpacked<CData/*7:0*/, 8> top__DOT__keyboard__DOT__fifo;

    // LOCAL VARIABLES
    CData/*0:0*/ top__DOT__keyboard__DOT____Vlvbound1;
    CData/*0:0*/ __Vclklast__TOP__clk;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop___024root);  ///< Copying not allowed
  public:
    Vtop___024root(const char* name);
    ~Vtop___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vtop__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard

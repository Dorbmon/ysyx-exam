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
    VL_OUT8(HEX0,6,0);
    VL_OUT8(HEX1,6,0);

    // LOCAL SIGNALS
    CData/*0:0*/ top__DOT__c;
    CData/*6:0*/ top__DOT__s0;
    CData/*6:0*/ top__DOT__s1;
    CData/*6:0*/ top__DOT__count;
    IData/*31:0*/ top__DOT__timer1__DOT__count;

    // LOCAL VARIABLES
    CData/*0:0*/ __VinpClk__TOP__top__DOT__c;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP____VinpClk__TOP__top__DOT__c;
    CData/*0:0*/ __Vchglast__TOP__top__DOT__c;
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

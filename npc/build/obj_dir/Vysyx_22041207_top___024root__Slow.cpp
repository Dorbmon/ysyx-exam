// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_22041207_top.h for the primary calling header

#include "Vysyx_22041207_top___024root.h"
#include "Vysyx_22041207_top__Syms.h"

//==========


void Vysyx_22041207_top___024root___ctor_var_reset(Vysyx_22041207_top___024root* vlSelf);

Vysyx_22041207_top___024root::Vysyx_22041207_top___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vysyx_22041207_top___024root___ctor_var_reset(this);
}

void Vysyx_22041207_top___024root::__Vconfigure(Vysyx_22041207_top__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vysyx_22041207_top___024root::~Vysyx_22041207_top___024root() {
}

void Vysyx_22041207_top___024root___eval_initial(Vysyx_22041207_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_22041207_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_22041207_top___024root___eval_initial\n"); );
}

void Vysyx_22041207_top___024root___eval_settle(Vysyx_22041207_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_22041207_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_22041207_top___024root___eval_settle\n"); );
}

void Vysyx_22041207_top___024root___final(Vysyx_22041207_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_22041207_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_22041207_top___024root___final\n"); );
}

void Vysyx_22041207_top___024root___ctor_var_reset(Vysyx_22041207_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vysyx_22041207_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_22041207_top___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->inst = 0;
    vlSelf->pc = 0;
}

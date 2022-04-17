// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop___024root.h"
#include "Vtop__Syms.h"

//==========

VL_INLINE_OPT void Vtop___024root___combo__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___combo__TOP__1\n"); );
    // Body
    if (vlSelf->e) {
        vlSelf->top__DOT__i = 8U;
    }
    vlSelf->y = 0U;
    vlSelf->indicator = 0U;
    if (vlSelf->e) {
        if ((1U & (IData)(vlSelf->x))) {
            vlSelf->y = 0U;
        }
        if ((2U & (IData)(vlSelf->x))) {
            vlSelf->y = 1U;
        }
        if ((4U & (IData)(vlSelf->x))) {
            vlSelf->y = 2U;
        }
        if ((8U & (IData)(vlSelf->x))) {
            vlSelf->y = 3U;
        }
        if ((0x10U & (IData)(vlSelf->x))) {
            vlSelf->y = 4U;
        }
        if ((0x20U & (IData)(vlSelf->x))) {
            vlSelf->y = 5U;
        }
        if ((0x40U & (IData)(vlSelf->x))) {
            vlSelf->y = 6U;
        }
        if ((0x80U & (IData)(vlSelf->x))) {
            vlSelf->y = 7U;
        }
        vlSelf->indicator = (0U != (IData)(vlSelf->y));
    } else {
        vlSelf->y = 0U;
    }
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Body
    Vtop___024root___combo__TOP__1(vlSelf);
}

QData Vtop___024root___change_request_1(Vtop___024root* vlSelf);

VL_INLINE_OPT QData Vtop___024root___change_request(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___change_request\n"); );
    // Body
    return (Vtop___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vtop___024root___change_request_1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->e & 0xfeU))) {
        Verilated::overWidthError("e");}
}
#endif  // VL_DEBUG

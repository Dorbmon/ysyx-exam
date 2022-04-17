// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop___024root.h"
#include "Vtop__Syms.h"

//==========

extern const VlUnpacked<CData/*2:0*/, 512> Vtop__ConstPool__TABLE_2ab4c310_0;
extern const VlUnpacked<CData/*0:0*/, 512> Vtop__ConstPool__TABLE_d484eecf_0;
extern const VlUnpacked<CData/*2:0*/, 512> Vtop__ConstPool__TABLE_4c2bd713_0;
extern const VlUnpacked<IData/*31:0*/, 512> Vtop__ConstPool__TABLE_508ee21b_0;
extern const VlUnpacked<CData/*6:0*/, 16> Vtop__ConstPool__TABLE_ad5609cf_0;

VL_INLINE_OPT void Vtop___024root___combo__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___combo__TOP__1\n"); );
    // Variables
    CData/*3:0*/ __Vtableidx2;
    SData/*8:0*/ __Vtableidx1;
    // Body
    __Vtableidx1 = (((IData)(vlSelf->x) << 1U) | (IData)(vlSelf->e));
    vlSelf->y = Vtop__ConstPool__TABLE_2ab4c310_0[__Vtableidx1];
    vlSelf->indicator = Vtop__ConstPool__TABLE_d484eecf_0
        [__Vtableidx1];
    if ((4U & Vtop__ConstPool__TABLE_4c2bd713_0[__Vtableidx1])) {
        vlSelf->top__DOT__i = Vtop__ConstPool__TABLE_508ee21b_0
            [__Vtableidx1];
    }
    __Vtableidx2 = (((IData)(vlSelf->y) << 1U) | (IData)(vlSelf->indicator));
    vlSelf->HEX0 = Vtop__ConstPool__TABLE_ad5609cf_0
        [__Vtableidx2];
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

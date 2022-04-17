// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop___024root.h"
#include "Vtop__Syms.h"

//==========

extern const VlUnpacked<CData/*6:0*/, 8> Vtop__ConstPool__TABLE_3c94bc34_0;

VL_INLINE_OPT void Vtop___024root___combo__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___combo__TOP__1\n"); );
    // Variables
    CData/*2:0*/ __Vtableidx1;
    CData/*2:0*/ __Vtableidx2;
    CData/*2:0*/ __Vtableidx3;
    // Body
    vlSelf->top__DOT__data = ((0x80U & (VL_REDXOR_32(
                                                     (0x1dU 
                                                      & (IData)(vlSelf->top__DOT__data))) 
                                        << 7U)) | (0x7fU 
                                                   & (IData)(vlSelf->top__DOT__data)));
    vlSelf->top__DOT__s0 = (0xffU & VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__data), (IData)(0xaU)));
    vlSelf->top__DOT__s1 = (0xffU & VL_MODDIV_III(32, 
                                                  VL_DIV_III(32, (IData)(vlSelf->top__DOT__data), (IData)(0xaU)), (IData)(0xaU)));
    vlSelf->top__DOT__s2 = (0xffU & VL_MODDIV_III(32, 
                                                  VL_DIV_III(32, (IData)(vlSelf->top__DOT__data), (IData)(0x64U)), (IData)(0xaU)));
    __Vtableidx1 = (7U & (IData)(vlSelf->top__DOT__s0));
    vlSelf->HEX0 = Vtop__ConstPool__TABLE_3c94bc34_0
        [__Vtableidx1];
    __Vtableidx2 = (7U & (IData)(vlSelf->top__DOT__s1));
    vlSelf->HEX1 = Vtop__ConstPool__TABLE_3c94bc34_0
        [__Vtableidx2];
    __Vtableidx3 = (7U & (IData)(vlSelf->top__DOT__s2));
    vlSelf->HEX2 = Vtop__ConstPool__TABLE_3c94bc34_0
        [__Vtableidx3];
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Body
    Vtop___024root___combo__TOP__1(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
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
    __req |= ((vlSelf->top__DOT__data ^ vlSelf->__Vchglast__TOP__top__DOT__data));
    VL_DEBUG_IF( if(__req && ((vlSelf->top__DOT__data ^ vlSelf->__Vchglast__TOP__top__DOT__data))) VL_DBG_MSGF("        CHANGE: /mnt/d/ysyx/ysyx-workbench/npc/vsrc/top.v:25: top.data\n"); );
    // Final
    vlSelf->__Vchglast__TOP__top__DOT__data = vlSelf->top__DOT__data;
    return __req;
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
}
#endif  // VL_DEBUG

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop___024root.h"
#include "Vtop__Syms.h"

//==========

VL_INLINE_OPT void Vtop___024root___sequent__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__1\n"); );
    // Variables
    IData/*31:0*/ __Vdly__top__DOT__timer1__DOT__count;
    // Body
    __Vdly__top__DOT__timer1__DOT__count = vlSelf->top__DOT__timer1__DOT__count;
    if ((0x17d783fU == vlSelf->top__DOT__timer1__DOT__count)) {
        vlSelf->top__DOT__c = (1U & (~ (IData)(vlSelf->top__DOT__c)));
        __Vdly__top__DOT__timer1__DOT__count = 0U;
    } else {
        __Vdly__top__DOT__timer1__DOT__count = ((IData)(1U) 
                                                + vlSelf->top__DOT__timer1__DOT__count);
    }
    vlSelf->top__DOT__timer1__DOT__count = __Vdly__top__DOT__timer1__DOT__count;
}

extern const VlUnpacked<CData/*6:0*/, 8> Vtop__ConstPool__TABLE_3c94bc34_0;

VL_INLINE_OPT void Vtop___024root___sequent__TOP__3(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___sequent__TOP__3\n"); );
    // Variables
    CData/*2:0*/ __Vtableidx1;
    CData/*2:0*/ __Vtableidx2;
    // Body
    vlSelf->top__DOT__count = (0x7fU & ((IData)(1U) 
                                        + (IData)(vlSelf->top__DOT__count)));
    vlSelf->top__DOT__s0 = (0x7fU & VL_MODDIV_III(32, (IData)(vlSelf->top__DOT__count), (IData)(0xaU)));
    vlSelf->top__DOT__s1 = (0x7fU & (VL_DIV_III(32, (IData)(vlSelf->top__DOT__count), (IData)(0xaU)) 
                                     - (IData)(vlSelf->top__DOT__s0)));
    if ((0x64U == (IData)(vlSelf->top__DOT__count))) {
        vlSelf->top__DOT__count = 0U;
    }
    __Vtableidx1 = (7U & (IData)(vlSelf->top__DOT__s0));
    vlSelf->HEX0 = Vtop__ConstPool__TABLE_3c94bc34_0
        [__Vtableidx1];
    __Vtableidx2 = (7U & (IData)(vlSelf->top__DOT__s1));
    vlSelf->HEX1 = Vtop__ConstPool__TABLE_3c94bc34_0
        [__Vtableidx2];
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vtop___024root___sequent__TOP__1(vlSelf);
    }
    if (((IData)(vlSelf->__VinpClk__TOP__top__DOT__c) 
         & (~ (IData)(vlSelf->__Vclklast__TOP____VinpClk__TOP__top__DOT__c)))) {
        Vtop___024root___sequent__TOP__3(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
    vlSelf->__Vclklast__TOP____VinpClk__TOP__top__DOT__c 
        = vlSelf->__VinpClk__TOP__top__DOT__c;
    vlSelf->__VinpClk__TOP__top__DOT__c = vlSelf->top__DOT__c;
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
    __req |= ((vlSelf->top__DOT__c ^ vlSelf->__Vchglast__TOP__top__DOT__c));
    VL_DEBUG_IF( if(__req && ((vlSelf->top__DOT__c ^ vlSelf->__Vchglast__TOP__top__DOT__c))) VL_DBG_MSGF("        CHANGE: /mnt/d/ysyx/ysyx-workbench/npc/vsrc/top.v:37: top.c\n"); );
    // Final
    vlSelf->__Vchglast__TOP__top__DOT__c = vlSelf->top__DOT__c;
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

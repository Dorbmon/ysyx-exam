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
    vlSelf->top__DOT____Vcellinp__i0____pinNumber4 
        = (0xa6U | ((0x200U & ((IData)(vlSelf->a) << 9U)) 
                    | ((0x40U & ((IData)(vlSelf->a) 
                                 << 5U)) | ((8U & ((IData)(vlSelf->a) 
                                                   << 1U)) 
                                            | (1U & 
                                               ((IData)(vlSelf->a) 
                                                >> 3U))))));
    vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list[0U] 
        = (7U & (IData)(vlSelf->top__DOT____Vcellinp__i0____pinNumber4));
    vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list[1U] 
        = (7U & ((IData)(vlSelf->top__DOT____Vcellinp__i0____pinNumber4) 
                 >> 3U));
    vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list[2U] 
        = (7U & ((IData)(vlSelf->top__DOT____Vcellinp__i0____pinNumber4) 
                 >> 6U));
    vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list[3U] 
        = (7U & ((IData)(vlSelf->top__DOT____Vcellinp__i0____pinNumber4) 
                 >> 9U));
    vlSelf->top__DOT__i0__DOT__i0__DOT__data_list[0U] 
        = (1U & vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list
           [0U]);
    vlSelf->top__DOT__i0__DOT__i0__DOT__key_list[0U] 
        = (3U & (vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list
                 [0U] >> 1U));
    vlSelf->top__DOT__i0__DOT__i0__DOT__data_list[1U] 
        = (1U & vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list
           [1U]);
    vlSelf->top__DOT__i0__DOT__i0__DOT__key_list[1U] 
        = (3U & (vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list
                 [1U] >> 1U));
    vlSelf->top__DOT__i0__DOT__i0__DOT__data_list[2U] 
        = (1U & vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list
           [2U]);
    vlSelf->top__DOT__i0__DOT__i0__DOT__key_list[2U] 
        = (3U & (vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list
                 [2U] >> 1U));
    vlSelf->top__DOT__i0__DOT__i0__DOT__data_list[3U] 
        = (1U & vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list
           [3U]);
    vlSelf->top__DOT__i0__DOT__i0__DOT__key_list[3U] 
        = (3U & (vlSelf->top__DOT__i0__DOT__i0__DOT__pair_list
                 [3U] >> 1U));
    vlSelf->top__DOT__i0__DOT__i0__DOT__lut_out = (
                                                   ((IData)(vlSelf->s) 
                                                    == 
                                                    vlSelf->top__DOT__i0__DOT__i0__DOT__key_list
                                                    [0U]) 
                                                   & vlSelf->top__DOT__i0__DOT__i0__DOT__data_list
                                                   [0U]);
    vlSelf->top__DOT__i0__DOT__i0__DOT__hit = ((IData)(vlSelf->s) 
                                               == vlSelf->top__DOT__i0__DOT__i0__DOT__key_list
                                               [0U]);
    vlSelf->top__DOT__i0__DOT__i0__DOT__lut_out = ((IData)(vlSelf->top__DOT__i0__DOT__i0__DOT__lut_out) 
                                                   | (((IData)(vlSelf->s) 
                                                       == 
                                                       vlSelf->top__DOT__i0__DOT__i0__DOT__key_list
                                                       [1U]) 
                                                      & vlSelf->top__DOT__i0__DOT__i0__DOT__data_list
                                                      [1U]));
    vlSelf->top__DOT__i0__DOT__i0__DOT__hit = ((IData)(vlSelf->top__DOT__i0__DOT__i0__DOT__hit) 
                                               | ((IData)(vlSelf->s) 
                                                  == 
                                                  vlSelf->top__DOT__i0__DOT__i0__DOT__key_list
                                                  [1U]));
    vlSelf->top__DOT__i0__DOT__i0__DOT__lut_out = ((IData)(vlSelf->top__DOT__i0__DOT__i0__DOT__lut_out) 
                                                   | (((IData)(vlSelf->s) 
                                                       == 
                                                       vlSelf->top__DOT__i0__DOT__i0__DOT__key_list
                                                       [2U]) 
                                                      & vlSelf->top__DOT__i0__DOT__i0__DOT__data_list
                                                      [2U]));
    vlSelf->top__DOT__i0__DOT__i0__DOT__hit = ((IData)(vlSelf->top__DOT__i0__DOT__i0__DOT__hit) 
                                               | ((IData)(vlSelf->s) 
                                                  == 
                                                  vlSelf->top__DOT__i0__DOT__i0__DOT__key_list
                                                  [2U]));
    vlSelf->top__DOT__i0__DOT__i0__DOT__lut_out = ((IData)(vlSelf->top__DOT__i0__DOT__i0__DOT__lut_out) 
                                                   | (((IData)(vlSelf->s) 
                                                       == 
                                                       vlSelf->top__DOT__i0__DOT__i0__DOT__key_list
                                                       [3U]) 
                                                      & vlSelf->top__DOT__i0__DOT__i0__DOT__data_list
                                                      [3U]));
    vlSelf->top__DOT__i0__DOT__i0__DOT__hit = ((IData)(vlSelf->top__DOT__i0__DOT__i0__DOT__hit) 
                                               | ((IData)(vlSelf->s) 
                                                  == 
                                                  vlSelf->top__DOT__i0__DOT__i0__DOT__key_list
                                                  [3U]));
    vlSelf->y = ((IData)(vlSelf->top__DOT__i0__DOT__i0__DOT__hit) 
                 & (IData)(vlSelf->top__DOT__i0__DOT__i0__DOT__lut_out));
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
    return __req;
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->a & 0xf0U))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->s & 0xfcU))) {
        Verilated::overWidthError("s");}
}
#endif  // VL_DEBUG

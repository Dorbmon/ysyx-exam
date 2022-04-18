// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__traceChgSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep);

void Vtop___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vtop___024root* const __restrict vlSelf = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        Vtop___024root__traceChgSub0((&vlSymsp->TOP), tracep);
    }
}

void Vtop___024root__traceChgSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
            tracep->chgBit(oldp+0,(vlSelf->top__DOT__overflow));
            tracep->chgCData(oldp+1,(vlSelf->top__DOT__keyboard__DOT__fifo
                                     [vlSelf->top__DOT__keyboard__DOT__r_ptr]),8);
            tracep->chgBit(oldp+2,(vlSelf->top__DOT__ready));
            tracep->chgCData(oldp+3,(vlSelf->top__DOT__s0),8);
            tracep->chgCData(oldp+4,(vlSelf->top__DOT__s1),8);
            tracep->chgSData(oldp+5,(vlSelf->top__DOT__keyboard__DOT__buffer),10);
            tracep->chgCData(oldp+6,(vlSelf->top__DOT__keyboard__DOT__fifo[0]),8);
            tracep->chgCData(oldp+7,(vlSelf->top__DOT__keyboard__DOT__fifo[1]),8);
            tracep->chgCData(oldp+8,(vlSelf->top__DOT__keyboard__DOT__fifo[2]),8);
            tracep->chgCData(oldp+9,(vlSelf->top__DOT__keyboard__DOT__fifo[3]),8);
            tracep->chgCData(oldp+10,(vlSelf->top__DOT__keyboard__DOT__fifo[4]),8);
            tracep->chgCData(oldp+11,(vlSelf->top__DOT__keyboard__DOT__fifo[5]),8);
            tracep->chgCData(oldp+12,(vlSelf->top__DOT__keyboard__DOT__fifo[6]),8);
            tracep->chgCData(oldp+13,(vlSelf->top__DOT__keyboard__DOT__fifo[7]),8);
            tracep->chgCData(oldp+14,(vlSelf->top__DOT__keyboard__DOT__w_ptr),3);
            tracep->chgCData(oldp+15,(vlSelf->top__DOT__keyboard__DOT__r_ptr),3);
            tracep->chgCData(oldp+16,(vlSelf->top__DOT__keyboard__DOT__count),4);
            tracep->chgCData(oldp+17,(vlSelf->top__DOT__keyboard__DOT__ps2_clk_sync),3);
            tracep->chgBit(oldp+18,((IData)((4U == 
                                             (6U & (IData)(vlSelf->top__DOT__keyboard__DOT__ps2_clk_sync))))));
            tracep->chgCData(oldp+19,((7U & (IData)(vlSelf->top__DOT__s0))),3);
            tracep->chgCData(oldp+20,((7U & (IData)(vlSelf->top__DOT__s1))),3);
        }
        tracep->chgBit(oldp+21,(vlSelf->clk));
        tracep->chgBit(oldp+22,(vlSelf->clrn));
        tracep->chgBit(oldp+23,(vlSelf->ps2_clk));
        tracep->chgBit(oldp+24,(vlSelf->ps2_data));
        tracep->chgCData(oldp+25,(vlSelf->HEX0),7);
        tracep->chgCData(oldp+26,(vlSelf->HEX1),7);
        tracep->chgCData(oldp+27,(vlSelf->HEX2),7);
    }
}

void Vtop___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    Vtop___024root* const __restrict vlSelf = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
        vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    }
}

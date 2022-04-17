// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__traceInitSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vtop___024root__traceInitTop(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vtop___024root__traceInitSub0(vlSelf, tracep);
    }
}

void Vtop___024root__traceInitSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBus(c+6,"HEX0", false,-1, 6,0);
        tracep->declBus(c+7,"HEX1", false,-1, 6,0);
        tracep->declBit(c+8,"clk", false,-1);
        tracep->declBus(c+6,"top HEX0", false,-1, 6,0);
        tracep->declBus(c+7,"top HEX1", false,-1, 6,0);
        tracep->declBit(c+8,"top clk", false,-1);
        tracep->declBit(c+9,"top c", false,-1);
        tracep->declBus(c+1,"top s0", false,-1, 6,0);
        tracep->declBus(c+2,"top s1", false,-1, 6,0);
        tracep->declBus(c+3,"top count", false,-1, 6,0);
        tracep->declBit(c+8,"top timer1 clk", false,-1);
        tracep->declBit(c+9,"top timer1 c", false,-1);
        tracep->declBus(c+10,"top timer1 count", false,-1, 31,0);
        tracep->declBus(c+4,"top seg0 b", false,-1, 2,0);
        tracep->declBus(c+6,"top seg0 h", false,-1, 6,0);
        tracep->declBus(c+5,"top seg1 b", false,-1, 2,0);
        tracep->declBus(c+7,"top seg1 h", false,-1, 6,0);
    }
}

void Vtop___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) VL_ATTR_COLD;
void Vtop___024root__traceChgTop0(void* voidSelf, VerilatedVcd* tracep);
void Vtop___024root__traceCleanup(void* voidSelf, VerilatedVcd* /*unused*/);

void Vtop___024root__traceRegister(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        tracep->addFullCb(&Vtop___024root__traceFullTop0, vlSelf);
        tracep->addChgCb(&Vtop___024root__traceChgTop0, vlSelf);
        tracep->addCleanupCb(&Vtop___024root__traceCleanup, vlSelf);
    }
}

void Vtop___024root__traceFullSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) VL_ATTR_COLD;

void Vtop___024root__traceFullTop0(void* voidSelf, VerilatedVcd* tracep) {
    Vtop___024root* const __restrict vlSelf = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    {
        Vtop___024root__traceFullSub0((&vlSymsp->TOP), tracep);
    }
}

void Vtop___024root__traceFullSub0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlSelf->top__DOT__s0),7);
        tracep->fullCData(oldp+2,(vlSelf->top__DOT__s1),7);
        tracep->fullCData(oldp+3,(vlSelf->top__DOT__count),7);
        tracep->fullCData(oldp+4,((7U & (IData)(vlSelf->top__DOT__s0))),3);
        tracep->fullCData(oldp+5,((7U & (IData)(vlSelf->top__DOT__s1))),3);
        tracep->fullCData(oldp+6,(vlSelf->HEX0),7);
        tracep->fullCData(oldp+7,(vlSelf->HEX1),7);
        tracep->fullBit(oldp+8,(vlSelf->clk));
        tracep->fullBit(oldp+9,(vlSelf->top__DOT__c));
        tracep->fullIData(oldp+10,(vlSelf->top__DOT__timer1__DOT__count),32);
    }
}

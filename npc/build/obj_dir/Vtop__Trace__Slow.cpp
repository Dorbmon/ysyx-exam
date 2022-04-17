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
        tracep->declBus(c+7,"HEX0", false,-1, 6,0);
        tracep->declBus(c+8,"HEX1", false,-1, 6,0);
        tracep->declBus(c+9,"HEX2", false,-1, 6,0);
        tracep->declBit(c+10,"clk", false,-1);
        tracep->declBus(c+7,"top HEX0", false,-1, 6,0);
        tracep->declBus(c+8,"top HEX1", false,-1, 6,0);
        tracep->declBus(c+9,"top HEX2", false,-1, 6,0);
        tracep->declBit(c+10,"top clk", false,-1);
        tracep->declBit(c+12,"top c", false,-1);
        tracep->declBus(c+1,"top s0", false,-1, 7,0);
        tracep->declBus(c+2,"top s1", false,-1, 7,0);
        tracep->declBus(c+3,"top s2", false,-1, 7,0);
        tracep->declBus(c+13,"top count", false,-1, 7,0);
        tracep->declBus(c+11,"top data", false,-1, 7,0);
        tracep->declBus(c+4,"top seg0 b", false,-1, 2,0);
        tracep->declBus(c+7,"top seg0 h", false,-1, 6,0);
        tracep->declBus(c+5,"top seg1 b", false,-1, 2,0);
        tracep->declBus(c+8,"top seg1 h", false,-1, 6,0);
        tracep->declBus(c+6,"top seg2 b", false,-1, 2,0);
        tracep->declBus(c+9,"top seg2 h", false,-1, 6,0);
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
        tracep->fullCData(oldp+1,(vlSelf->top__DOT__s0),8);
        tracep->fullCData(oldp+2,(vlSelf->top__DOT__s1),8);
        tracep->fullCData(oldp+3,(vlSelf->top__DOT__s2),8);
        tracep->fullCData(oldp+4,((7U & (IData)(vlSelf->top__DOT__s0))),3);
        tracep->fullCData(oldp+5,((7U & (IData)(vlSelf->top__DOT__s1))),3);
        tracep->fullCData(oldp+6,((7U & (IData)(vlSelf->top__DOT__s2))),3);
        tracep->fullCData(oldp+7,(vlSelf->HEX0),7);
        tracep->fullCData(oldp+8,(vlSelf->HEX1),7);
        tracep->fullCData(oldp+9,(vlSelf->HEX2),7);
        tracep->fullBit(oldp+10,(vlSelf->clk));
        tracep->fullCData(oldp+11,(vlSelf->top__DOT__data),8);
        tracep->fullBit(oldp+12,(vlSelf->top__DOT__c));
        tracep->fullCData(oldp+13,(vlSelf->top__DOT__count),8);
    }
}

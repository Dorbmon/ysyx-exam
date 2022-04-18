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
        tracep->declBit(c+1,"clk", false,-1);
        tracep->declBit(c+2,"clrn", false,-1);
        tracep->declBit(c+3,"ps2_clk", false,-1);
        tracep->declBit(c+4,"ps2_data", false,-1);
        tracep->declBus(c+5,"HEX0", false,-1, 6,0);
        tracep->declBus(c+6,"HEX1", false,-1, 6,0);
        tracep->declBus(c+7,"HEX2", false,-1, 6,0);
        tracep->declBit(c+1,"top clk", false,-1);
        tracep->declBit(c+2,"top clrn", false,-1);
        tracep->declBit(c+3,"top ps2_clk", false,-1);
        tracep->declBit(c+4,"top ps2_data", false,-1);
        tracep->declBit(c+10,"top nextdata_n", false,-1);
        tracep->declBit(c+11,"top overflow", false,-1);
        tracep->declBus(c+12,"top data", false,-1, 7,0);
        tracep->declBit(c+13,"top ready", false,-1);
        tracep->declBus(c+5,"top HEX0", false,-1, 6,0);
        tracep->declBus(c+6,"top HEX1", false,-1, 6,0);
        tracep->declBus(c+7,"top HEX2", false,-1, 6,0);
        tracep->declBus(c+8,"top s0", false,-1, 7,0);
        tracep->declBus(c+9,"top s1", false,-1, 7,0);
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
        tracep->fullBit(oldp+1,(vlSelf->clk));
        tracep->fullBit(oldp+2,(vlSelf->clrn));
        tracep->fullBit(oldp+3,(vlSelf->ps2_clk));
        tracep->fullBit(oldp+4,(vlSelf->ps2_data));
        tracep->fullCData(oldp+5,(vlSelf->HEX0),7);
        tracep->fullCData(oldp+6,(vlSelf->HEX1),7);
        tracep->fullCData(oldp+7,(vlSelf->HEX2),7);
        tracep->fullCData(oldp+8,(vlSelf->top__DOT__s0),8);
        tracep->fullCData(oldp+9,(vlSelf->top__DOT__s1),8);
        tracep->fullBit(oldp+10,(vlSelf->top__DOT__nextdata_n));
        tracep->fullBit(oldp+11,(vlSelf->top__DOT__overflow));
        tracep->fullCData(oldp+12,(vlSelf->top__DOT__data),8);
        tracep->fullBit(oldp+13,(vlSelf->top__DOT__ready));
    }
}

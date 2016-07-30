//******************************************************************
// main.cpp - put it all together
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"
#include "tb.h"


int sc_main(int argc, char *argv[]) {
    
	// signals
	sc_signal<sc_uint<word_length> > A_IN;
	sc_signal<sc_uint<word_length> > B_IN;
	sc_signal<sc_uint<word_length> > Z_OUT;
	sc_signal<sc_logic> carry_OUT;
	
	// clock
	//sc_signal<sc_logic> reset, load;
	sc_clock clock("clock", 10, SC_NS, 0.5, 0, SC_NS, true);


    // instances
    add ADD("ADD"); 
	stim STIM("STIM");
	mon MON("MON");

	// adder interconnections
	ADD.A_IN(A_IN);
	ADD.B_IN(B_IN);	
	ADD.Z_OUT(Z_OUT);
	ADD.carry_OUT(carry_OUT);

    STIM.A_IN(A_IN);
    STIM.B_IN(B_IN);
    STIM.clock(clock);
    
    MON.Z_OUT(Z_OUT);
    MON.carry_OUT(carry_OUT);
    MON.clock(clock);

	// // REG interconnections
	// REG.A_IN(A_IN);
	// REG.B_OUT(B_OUT);	
	// REG.reset(reset);
	// REG.load(load);
	// REG.clock(clock);

 //    STIM.A_IN(A_IN);
	// STIM.reset(reset);
	// STIM.load(load);
 //    STIM.clock(clock);
    
 //    MON.B_OUT(B_OUT);
 //    MON.clock(clock);
	
	/*
	//traces       
	sc_trace_file *tf = sc_create_vcd_trace_file("gcd_trace");
	tf->set_time_unit(1, SC_NS);
	sc_trace(tf, X_IN, "X_IN");
	sc_trace(tf, Y_IN, "Y_IN");
	sc_trace(tf, reset, "reset");
	sc_trace(tf, clock, "clock");
	sc_trace(tf, Z_OUT, "Z_OUT"); 

	sc_trace(tf, GCD.xmux_sel, "xmux_sel");
	sc_trace(tf, GCD.ymux_sel, "ymux_sel");
	sc_trace(tf, GCD.amux_sel, "amux_sel");
	sc_trace(tf, GCD.bmux_sel, "bmux_sel");
	sc_trace(tf, GCD.xreg_load, "xreg_load");
	sc_trace(tf, GCD.yreg_load, "yreg_load");
	sc_trace(tf, GCD.zreg_load, "zreg_load");

	sc_trace(tf, GCD.EQ, "EQ");
	sc_trace(tf, GCD.GT, "GT");
	sc_trace(tf, GCD.LT, "LT");

	sc_trace(tf, GCD.DP.x_n, "x_n");
	sc_trace(tf, GCD.DP.y_n, "y_n");
	sc_trace(tf, GCD.DP.x, "x");
	sc_trace(tf, GCD.DP.y, "y");
	sc_trace(tf, GCD.DP.sub_A, "sub_A");
	sc_trace(tf, GCD.DP.sub_B, "sub_B");
	sc_trace(tf, GCD.DP.sub_out, "sub_out");
    
	sc_trace(tf, GCD.CL.state, "state");
	sc_trace(tf, GCD.CL.next_state, "next_state");
	*/
      
    
	sc_start();

	//sc_close_vcd_trace_file(tf);
		
	return(0);
}

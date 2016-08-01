//******************************************************************
// main.cpp - put it all together
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"
#include "tb.h"
#include "datapath.h"
#include "ctrl.h"


int sc_main(int argc, char *argv[]) {
    
	// signals

	sc_signal<sc_uint<input_length> > multiplier, multiplicand, HI_mux_zero, carry_mux_zero, LO_LSB, HI_LSB;
	sc_signal<sc_uint<product_length> > product;
	
	sc_signal<sc_logic> HI_mux_sel, LO_mux_sel, HI_mux2_sel, carry_mux_sel; 
    sc_signal<sc_logic> HI_reg_load, LO_reg_load, rshift_load;
    sc_signal<sc_logic> DONE;

	sc_signal<sc_logic> reset;

	//sc_signal<sc_uint<input_length> > HI_OUT;
	//sc_signal<sc_uint<input_length> > LO_OUT;
	//sc_signal<sc_uint<product_length> > Z_OUT;
	//sc_signal<sc_logic> carry_IN;
	//sc_signal<sc_logic> carry_OUT;
	
	// clock
	//sc_signal<sc_logic> reset, load;
	sc_clock clock("clock", 10, SC_NS, 0.5, 0, SC_NS, true);

	// instancess
	datapath DP("DP"); 
	ctrl CTRL("CTRL");
	stim STIM("STIM");
	mon MON("MON");

	//interconnections
	DP.reset(reset);
	DP.clock(clock);
	DP.multiplier(multiplier);
	DP.multiplicand(multiplicand);
	DP.HI_mux_zero(HI_mux_zero);
	DP.carry_mux_zero(carry_mux_zero);
	DP.product(product);
	DP.LO_LSB(LO_LSB);
	DP.HI_LSB(HI_LSB);
	DP.HI_mux_sel(HI_mux_sel);
	DP.LO_mux_sel(LO_mux_sel);
	DP.HI_mux2_sel(HI_mux2_sel);
	DP.carry_mux_sel(carry_mux_sel);
	DP.HI_reg_load(HI_reg_load);
	DP.LO_reg_load(LO_reg_load);
	DP.rshift_load(rshift_load);

	CTRL.reset(reset);
	CTRL.clock(clock);
	CTRL.LO_LSB(LO_LSB);
	CTRL.HI_mux_sel(HI_mux_sel);
	CTRL.LO_mux_sel(LO_mux_sel);
	CTRL.HI_mux2_sel(HI_mux2_sel);
	CTRL.carry_mux_sel(carry_mux_sel);
	CTRL.HI_reg_load(HI_reg_load);
	CTRL.LO_reg_load(LO_reg_load);
	CTRL.rshift_load(rshift_load);
	CTRL.DONE(DONE);

	STIM.reset(reset);
	STIM.clock(clock);
	STIM.HI_mux_zero(HI_mux_zero);
	STIM.carry_mux_zero(carry_mux_zero);
	STIM.multiplier(multiplier);
	STIM.multiplicand(multiplicand);

	MON.clock(clock);
	MON.product(product);
	MON.DONE(DONE);



    // instances
    /*
    splitter SPLITTER("RSHIFT"); 
	stim STIM("STIM");
	mon MON("MON");

	// interconnections
	


	SPLITTER.A_IN(A_IN);	
	SPLITTER.HI_OUT(HI_OUT);
	SPLITTER.LO_OUT(LO_OUT);

    STIM.A_IN(A_IN);
    STIM.clock(clock);
    
    MON.HI_OUT(HI_OUT);
    MON.LO_OUT(LO_OUT);
    MON.clock(clock);
    */



	// adder interconnections
	// ADD.A_IN(A_IN);
	// ADD.B_IN(B_IN);	
	// ADD.Z_OUT(Z_OUT);
	// ADD.carry_OUT(carry_OUT);

 //    STIM.A_IN(A_IN);
 //    STIM.B_IN(B_IN);
 //    STIM.clock(clock);
    
 //    MON.Z_OUT(Z_OUT);
 //    MON.carry_OUT(carry_OUT);
 //    MON.clock(clock);

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
	
	
	//traces       
	sc_trace_file *tf = sc_create_vcd_trace_file("gcd_trace");
	tf->set_time_unit(1, SC_NS);
	//sc_trace(tf, X_IN, "X_IN");
	//sc_trace(tf, Y_IN, "Y_IN");
	sc_trace(tf, reset, "reset");
	sc_trace(tf, clock, "clock");
	//sc_trace(tf, Z_OUT, "Z_OUT"); 

	sc_trace(tf, DP.LO_mux.A_IN, "LO_mux.A_IN");
	sc_trace(tf, DP.LO_mux.B_IN, "LO_mux.B_IN");
	sc_trace(tf, DP.LO_mux.Z_OUT, "LO_mux.Z_OUT");
	sc_trace(tf, DP.LO_mux.sel, "LO_mux.sel");

	sc_trace(tf, DP.LO_reg.A_IN, "LO_reg.A_IN");
	sc_trace(tf, DP.LO_reg.load, "LO_reg.load");
	sc_trace(tf, DP.LO_reg.Z_OUT, "LO_reg.Z_OUT");
	sc_trace(tf, DP.LO_reg.LSB, "LO_reg.LSB");

	sc_trace(tf, DP.HI_mux.A_IN, "HI_mux.A_IN");
	sc_trace(tf, DP.HI_mux.B_IN, "HI_mux.B_IN");
	sc_trace(tf, DP.HI_mux.Z_OUT, "HI_mux.Z_OUT");
	sc_trace(tf, DP.HI_mux.sel, "HI_mux.sel");

	sc_trace(tf, DP.rshifter.A_IN, "rshifter.A_IN");
	sc_trace(tf, DP.rshifter.B_IN, "rshifter.B_IN");
	sc_trace(tf, DP.rshifter.carry_IN, "rshifter.carry_IN");
	sc_trace(tf, DP.rshifter.Z_OUT, "rshifter.Z_OUT");
	sc_trace(tf, DP.rshifter.product_OUT, "rshifter.product_OUT");
	sc_trace(tf, DP.rshifter.load, "rshifter.load");
	//sc_trace(tf, DP.product, "DP.product");

	sc_trace(tf, DP.adder.A_IN, "adder.A_IN");
	sc_trace(tf, DP.adder.B_IN, "adder.B_IN");
	sc_trace(tf, DP.adder.Z_OUT, "adder.Z_OUT");
	sc_trace(tf, DP.adder.carry_OUT, "adder.carry_OUT");



	// sc_trace(tf, GCD.ymux_sel, "ymux_sel");
	// sc_trace(tf, GCD.amux_sel, "amux_sel");
	// sc_trace(tf, GCD.bmux_sel, "bmux_sel");
	// sc_trace(tf, GCD.xreg_load, "xreg_load");
	// sc_trace(tf, GCD.yreg_load, "yreg_load");
	// sc_trace(tf, GCD.zreg_load, "zreg_load");

	// sc_trace(tf, GCD.EQ, "EQ");
	// sc_trace(tf, GCD.GT, "GT");
	// sc_trace(tf, GCD.LT, "LT");

	// sc_trace(tf, GCD.DP.x_n, "x_n");
	// sc_trace(tf, GCD.DP.y_n, "y_n");
	// sc_trace(tf, GCD.DP.x, "x");
	// sc_trace(tf, GCD.DP.y, "y");
	// sc_trace(tf, GCD.DP.sub_A, "sub_A");
	// sc_trace(tf, GCD.DP.sub_B, "sub_B");
	// sc_trace(tf, GCD.DP.sub_out, "sub_out");
    
	// sc_trace(tf, GCD.CL.state, "state");
	// sc_trace(tf, GCD.CL.next_state, "next_state");
	
      
    
	sc_start(3000, SC_NS);

	sc_close_vcd_trace_file(tf);
		
	return(0);
}

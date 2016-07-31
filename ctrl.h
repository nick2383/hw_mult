//******************************************************************
// ctrl.h - header file for datapath controller
// Author: Nick Birch
// Date: July 31, 2016
//******************************************************************

#ifndef CONTROL_H
#define CONTROL_H
#include "systemc.h"

enum ctrl_state {S0_BEGIN, S1_CHECK, S2_ADD, S2_DO_NOTHING, S3_FINISH};
    
//*************************
// controller module
//*************************
SC_MODULE(ctrl) {
    // declare ports
    sc_out<sc_logic> HI_mux_sel, LO_mux_sel, HI_mux2_sel, carry_mux_sel, rshift_load;
    sc_out<sc_logic> HI_reg_load, LO_reg_load;

    sc_in<sc_logic> LO_LSB;

    sc_in<sc_logic> reset;
    sc_in_clk clock;
    
    // signals
    sc_signal<ctrl_state> state, next_state;

    // variables
    int counter;
    
    // functions   
    void state_transition();
    void state_output();
    void state_reg();
   
    SC_CTOR(ctrl) { 
    	SC_METHOD(state_transition);
    	   sensitive << state;
    	SC_METHOD(state_output);
    	   sensitive << state;	
    	SC_CTHREAD(state_reg, clock.pos());
    }
};

#endif
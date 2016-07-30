//******************************************************************
// modules.h - Modules for hardware multiplier
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#ifndef MODULES_H
#define MODULES_H
#include "systemc.h"


#define word_length 16

//*************************
// add - adds number A and b
//*************************
SC_MODULE(add) {
    // ports
    sc_in< sc_uint<word_length> > A; 
    sc_in< sc_uint<word_length> > B;	
    sc_out< sc_uint<word_length> > OUT;
    sc_out< sc_uint<word_length> > COUT;

    void add_process();
    
    SC_CTOR(add) {
        SC_METHOD(add_process);
        sensitive << A << B;
    }
};

//*************************
// mux2 - 2:1 multiplexer
//*************************
SC_MODULE(mux2) {
    // ports
    sc_in<sc_logic> sel;
    sc_in< sc_uint<word_length> > A; 
    sc_in< sc_uint<word_length> > B;	
    sc_out< sc_uint<word_length> > OUT;

    void mux2_process();
    
    SC_CTOR(mux2) {
        SC_METHOD(mux2_process);
        sensitive << sel << A << B;
    }
};

//*************************
// reg - data register
//*************************
SC_MODULE(reg) {
    // ports
    sc_in<sc_logic> reset, load;
    sc_in_clk clock;
    sc_in< sc_uint<word_length> > A_IN; 
    sc_out< sc_uint<word_length> > B_OUT;	

    void reg_process();
    
    SC_CTOR(reg) {
        SC_CTHREAD(reg_process, clock.pos());
    }
};

#endif
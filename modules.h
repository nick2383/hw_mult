//******************************************************************
// modules.h - Modules for hardware multiplier
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#ifndef MODULES_H
#define MODULES_H
#include "systemc.h"


#define input_length 16
#define product_length 32

//*************************
// add - adds number A and b
//*************************
SC_MODULE(add) {
    // ports
    sc_in< sc_uint<input_length> > A_IN; 
    sc_in< sc_uint<input_length> > B_IN;	
    sc_out< sc_uint<input_length> > Z_OUT;
    sc_out< sc_uint<input_length> > carry_OUT;

    void add_process();
    
    SC_CTOR(add) {
        SC_METHOD(add_process);
        sensitive << A_IN << B_IN;
    }
};

//*************************
// mux2 - 2:1 multiplexer
//*************************
SC_MODULE(mux2) {
    // ports
    sc_in<sc_logic> sel;
    sc_in< sc_uint<input_length> > A_IN; 
    sc_in< sc_uint<input_length> > B_IN;	
    sc_out< sc_uint<input_length> > Z_OUT;

    void mux2_process();
    
    SC_CTOR(mux2) {
        SC_METHOD(mux2_process);
        sensitive << sel << A_IN << B_IN;
    }
};

//*************************
// reg - data register
//*************************
SC_MODULE(reg) {
    // ports
    sc_in<sc_logic> reset, load;
    sc_in_clk clock;
    sc_in< sc_uint<input_length> > A_IN; 
    sc_out< sc_uint<input_length> > Z_OUT;	
    sc_out<sc_logic> LSB;

    void reg_process();
    
    SC_CTOR(reg) {
        SC_CTHREAD(reg_process, clock.pos());
    }
};

//*************************
// rshift - right bit shifter
//*************************
SC_MODULE(rshift) {
    // ports
    sc_in< sc_uint<input_length> > A_IN;
    sc_in< sc_uint<input_length> > B_IN;
    sc_in<sc_logic> carry_IN;
    sc_in<sc_logic> load;
    sc_out< sc_uint<product_length> > Z_OUT; 

    void rshift_process();
    
    SC_CTOR(rshift) {
        SC_METHOD(rshift_process);
        sensitive << load;
    }
};

//*************************
// splitter - 2:1 bit splitter
//*************************
SC_MODULE(splitter) {
    // ports
    sc_in< sc_uint<product_length> > A_IN;
    sc_out< sc_uint<input_length> > LO_OUT;
    sc_out< sc_uint<input_length> > HI_OUT;

    void splitter_process();
    
    SC_CTOR(splitter) {
        SC_METHOD(splitter_process);
        sensitive << A_IN;
    }
};

#endif
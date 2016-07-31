//******************************************************************
// rshift.cpp - right bit shifter
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"

void rshift::rshift_process() {
    
    // temporary variables
    sc_uint<product_length> temp_output = 0;
    temp_output = (A_IN.read() << multiplier_length) + B_IN.read();
    temp_output = temp_output >> 1;

    if(carry_IN == SC_LOGIC_1){
        temp_output = (1<<31) + temp_output;
    }
    
    // write result to output port
    Z_OUT.write(temp_output);
}

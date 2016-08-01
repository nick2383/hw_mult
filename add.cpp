//******************************************************************
// add.cpp - processes for adder
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"

void add::add_process() {
    
    // temporary variables
    sc_uint<input_length> a_in_temp = A_IN.read();
    sc_uint<input_length> b_in_temp = B_IN.read();
    sc_uint<product_length> sum_temp = a_in_temp + b_in_temp;

    // check for carry out bit and set or reset carry_OUT flag accordingly
    if(sum_temp > 15){
    	//if(sum_temp > 65535)
    	carry_OUT.write(1);
    }
    else{
    	carry_OUT.write(0);
    }

    // write result to output port
    Z_OUT.write(a_in_temp + b_in_temp);
}
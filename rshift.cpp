//******************************************************************
// rshift.cpp - right bit shifter
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"

void rshift::rshift_process() {

    while (1) {
        if (reset.read() == SC_LOGIC_1) {
            Z_OUT.write(0);
        }
        else if (load.read() == SC_LOGIC_1) {
            // temporary variables
            sc_uint<product_length> temp_output = 0;
            temp_output = (A_IN.read() << input_length) + B_IN.read();
            temp_output = temp_output >> 1;

            if(carry_IN.read() == 1){
                temp_output = (1<<31) + temp_output;
                //temp_output = (1<<7) + temp_output;
            }
            
            // write result to output port
            Z_OUT.write(temp_output);
            product_OUT.write(temp_output);
            
        }

    wait();
    }
}

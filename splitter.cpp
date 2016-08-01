//******************************************************************
// splitter.cpp - bit splitter
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"

void splitter::splitter_process() {
    
    // temporary variables
    sc_uint<input_length> temp_lo_out = 0;
    sc_uint<input_length> temp_hi_out = 0;

    // mask upper two bytes
    temp_lo_out = A_IN.read() & 0x0F;
    //temp_lo_out = A_IN.read() & 0x0000FFFF;
    // mask lowwer two bytes and shift right
    temp_hi_out = (A_IN.read() & 0xF0) >> 4;
    //temp_hi_out = (A_IN.read() & 0xFFFF0000) >> 16;
    // write results to output ports
    HI_OUT.write(temp_hi_out);
    LO_OUT.write(temp_lo_out);
}

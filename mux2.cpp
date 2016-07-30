//******************************************************************
// mux2.cpp - processes for mutliplexer
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"

void mux2::mux2_process() {
    
    if (sel.read() == SC_LOGIC_1) 
        OUT.write(B.read());
    else 
        OUT.write(A.read());
}
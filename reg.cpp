//******************************************************************
// reg.cpp - processes for data register
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"

void reg::reg_process() {
    
    while (1) {
        if (reset.read() == SC_LOGIC_1) {
        	B_OUT.write(0);
        }
        else if (load.read() == SC_LOGIC_1) {
        	B_OUT.write(A_IN.read());
        }
	wait();
    }
}
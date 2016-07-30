//******************************************************************
// add.cpp - processes for adder
// Author: Nick Birch
// Date: July 30, 2016
//******************************************************************
#include "systemc.h"
#include "modules.h"

void add::add_process() {
    
    OUT.write(A.read() + B.read());
}
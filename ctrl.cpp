//******************************************************************
// ctrl.cpp - controller for datapath
// Author: Nick Birch
// Date: July 31, 2016
//******************************************************************
#include <systemc.h>
#include "ctrl.h"

void ctrl::state_reg() {
  while(1) {
    if (reset.read() == SC_LOGIC_1) state.write(S0_BEGIN);
    else state.write(next_state.read());
    wait();
  }
}

void ctrl::state_transition() {

  // default: self-loop
  next_state.write(state.read());
  
  switch (state.read()) {

    case S0_BEGIN:
        next_state.write(S1_CHECK);
        break;
	
    case S1_CHECK:
        if(counter == 32){
          next_state.write(S3_FINISH);
        }
        else if (LO_LSB.read() == 1) {
          next_state.write(S2_ADD);
        }
	      else if (LO_LSB.read() == 0) [
          next_state.write(S2_DO_NOTHING);
        }
        break;

    case S2_ADD:
        next_state.write(S1_CHECK);
        break;

    case S2_DO_NOTHING:
        next_state.write(S1_CHECK);
        break;

    case S3_FINISH:
        break;
	
    default:
        break;
  }    
}


void ctrl::state_output() {
  // default: all outputs at zero
  HI_mux_sel.write(SC_LOGIC_0); 
  LO_mux_sel.write(SC_LOGIC_0);
  HI_mux2_sel.write(SC_LOGIC_0); 
  carry_mux_sel.write(SC_LOGIC_0);
  HI_reg_load.write(SC_LOGIC_0); 
  LO_reg_load.write(SC_LOGIC_0);
  
  switch (state.read()) {

    case S0_BEGIN:
        HI_mux_sel.write(SC_LOGIC_0);
	      HI_reg_load.write(SC_LOGIC_1);
	      LO_mux_sel.write(SC_LOGIC_0);
        LO_reg_load.write(SC_LOGIC_1);
        break;

    case S1_CHECK:
        counter = counter + 1;
        break;

    case S2_DO_NOTHING:
	      carry_mux_sel.write(SC_LOGIC_0);
	      HI_mux2_sel.write(SC_LOGIC_0);
        rshift_load.write(SC_LOGIC_1);
        rshift_load.write(SC_LOGIC_0);
        break;

    case S2_ADD:
	      carry_mux_sel.write(SC_LOGIC_1);
        HI_mux2_sel.write(SC_LOGIC_1);
        rshift_load.write(SC_LOGIC_1);
        rshift_load.write(SC_LOGIC_0);	    
        break;
    case S3_FINISH:
        cout << "done.."
        break;	
	
    default:
        break;
  }    
}
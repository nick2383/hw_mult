//******************************************************************
// ctrl.cpp - controller for datapath
// Author: Nick Birch
// Date: July 31, 2016
//******************************************************************
#include <systemc.h>
#include "ctrl.h"

void ctrl::state_reg() {
  while(1) {
    if (reset.read() == SC_LOGIC_1) {
      state.write(S0_BEGIN);
    }
    else state.write(next_state.read());
    wait();
  }
}

void ctrl::state_transition() {

  // default: self-loop
  next_state.write(state.read());
  
  switch (state.read()) {

    case S0_BEGIN:
        next_state.write(S1_COUNT);
        break;
	
    case S1_COUNT:
        if(counter == 32){
          next_state.write(S4_FINISH);
        }
        else {
          next_state.write(S2_CHECK);
        }
        break;

    case S2_CHECK:
        if (LO_LSB.read() == 1) {
          next_state.write(S3_ADD);
        }
        else if (LO_LSB.read() == 0) {
          next_state.write(S3_DO_NOTHING);
        }
        break;

    case S3_ADD:
        next_state.write(S1_COUNT);
        break;

    case S3_DO_NOTHING:
        next_state.write(S1_COUNT);
        break;

    case S4_FINISH:
        break;
	
    default:
        break;
  }    
}


void ctrl::state_output() {
  //default: all outputs at zero
  // HI_mux_sel.write(SC_LOGIC_1); 
  // LO_mux_sel.write(SC_LOGIC_1);
  // HI_mux2_sel.write(SC_LOGIC_0); 
  // carry_mux_sel.write(SC_LOGIC_0);
  // HI_reg_load.write(SC_LOGIC_0); 
  // LO_reg_load.write(SC_LOGIC_0);
  rshift_load.write(SC_LOGIC_1);
  
  switch (state.read()) {

    case S0_BEGIN:
        cout << "\n S0_BEGIN";
        HI_mux_sel.write(SC_LOGIC_0);
	      HI_reg_load.write(SC_LOGIC_1);
	      LO_mux_sel.write(SC_LOGIC_0);
        LO_reg_load.write(SC_LOGIC_1);
        break;

    case S1_COUNT:
        cout << "\n S1_COUNT counter = " << counter;
        counter = counter + 1;
        break;

    case S2_CHECK:
        LO_mux_sel.write(SC_LOGIC_1);
        HI_mux_sel.write(SC_LOGIC_1);
        break;

    case S3_DO_NOTHING:
        cout << " \n S3_DO_NOTHING";
	      carry_mux_sel.write(SC_LOGIC_0);
	      HI_mux2_sel.write(SC_LOGIC_0);
        //rshift_load.write(SC_LOGIC_1);
        //rshift_load.write(SC_LOGIC_0);
        break;

    case S3_ADD:
        cout << " \n S3_ADD";
        //HI_reg_load.write(SC_LOGIC_1);
        //LO_reg_load.write(SC_LOGIC_1);
	      carry_mux_sel.write(SC_LOGIC_1);
        HI_mux2_sel.write(SC_LOGIC_1);    
        break;

    case S4_FINISH:
        cout << " \n S4_FINISH";
        cout << "done..";
        break;	
	
    default:
        break;
  }    
}
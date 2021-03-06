//******************************************************************
// tb.h - testbench for modules
// Author: Nick Birch
// Date: July 31, 2016
//******************************************************************

#include "systemc.h"
#include "digit.h"
// #define input_length 4
// #define product_length 8
// #define input_length 16
// #define product_length 32

SC_MODULE(stim) {
    sc_out< sc_uint<NN_HALF_DIGIT_BITS> > multiplier, multiplicand, HI_mux_zero, carry_mux_zero;
    sc_out<sc_logic> reset;
    sc_in_clk clock;
    
    void stim_process(){

    	reset.write(SC_LOGIC_1);
    	reset.write(SC_LOGIC_0);
    	multiplier.write(65535);
    	multiplicand.write(65535);
    	wait();
		// cout << "\n Time = " << sc_time_stamp() << 
		// 	"  multiplier = " << multiplier.read() << 
		// 	"  multiplicand = " << multiplicand.read() << endl;
    	
    	/*
    	A_IN.write(2147549183);
		wait();
		cout << "Time = " << sc_time_stamp() << 
			"  A_IN = " << A_IN.read() << endl;
		*/

    	//****
		// SPLITTER stim
		//****
    	/*
    	A_IN.write(1);
    	B_IN.write(65535);
    	carry_IN.write(SC_LOGIC_1);
		wait();
		cout << "Time = " << sc_time_stamp() << 
			"  A_IN = " << A_IN.read() << 
			"  B_IN = " << B_IN.read() <<
			"  carry_IN = " << carry_IN.read() << endl;
		*/

		//****
		// REG stim
		//****

		/*
		reset.write(SC_LOGIC_1);
		wait();

		reset.write(SC_LOGIC_0);    	
	    A_IN.write(10);	
		wait();
		load.write(SC_LOGIC_1);
		wait();
		load.write(SC_LOGIC_0);
		wait();

		cout << "Time = " << sc_time_stamp() << 
			"  A_IN = " << A_IN.read() << endl; 

	    wait();
		wait();
				
		A_IN.write(5);
		wait();

		cout << "Time = " << sc_time_stamp() << 
			"  A_IN = " << A_IN.read() << endl;  
			
	    wait();
		wait();

		cout << "loading register from A_IN..." << endl;

		wait();
		load.write(SC_LOGIC_1);
		wait();
		load.write(SC_LOGIC_0);
		wait();
		*/
		 
	    //sc_stop();
        
    }
        
    SC_CTOR(stim) {
        SC_CTHREAD(stim_process, clock.pos());
    }  
};


SC_MODULE(mon) {
    sc_in< sc_uint<NN_DIGIT_BITS> > product;
    //sc_in< sc_uint<multiplier_length> > HI_OUT;
    sc_in<sc_logic> DONE;
    sc_in_clk clock;
    
    void mon_process(){
        
        while (1) {
	  		wait();
	  		if(DONE.read() == SC_LOGIC_1){
	  			cout <<"\n Product = " << product <<"\n";
	  			break;
	  		}
	  		// cout << " \n * Time = " << sc_time_stamp() << 
		  	// 	"  product = " << product.read() << endl;
    	}


        /*while (1) {
	  		wait();
	  		cout << " * Time = " << sc_time_stamp() << 
		  		"  HI_OUT = " << HI_OUT.read() << 
		  		"  LO_OUT = " << LO_OUT.read() << endl;
    	}
    	*/
    
    	// SPLITTER mon
    	//*****
    	/*
    	while (1) {
	  		wait();
	  		cout << " * Time = " << sc_time_stamp() << 
		  		"  Z_OUT = " << Z_OUT.read() << endl;
    	}
    	*/

    	/*
    	// REG mon
    	//*****
        while (1) {
	  		wait();
	  		cout << " * Time = " << sc_time_stamp() << 
		  		"  B_OUT = " << B_OUT.read() << endl;
    	}
    	*/        
    }
        
    SC_CTOR(mon) {
        SC_CTHREAD(mon_process, clock.pos());
    }  
};

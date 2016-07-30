/******************************************************************
* gcd_tb.h - Stimulus and Monitor for GCD
*
* Daler Rakhmatov
*****************************************************************/

#include "systemc.h"

SC_MODULE(stim) {
    sc_out< sc_uint<word_length> > A_IN;
    sc_out< sc_uint<word_length> > B_IN;
    //sc_out<sc_logic> reset, load;
    sc_in_clk clock;
    
    void stim_process(){

    	A_IN.write(65534);
    	B_IN.write(1);
		wait();
		cout << "Time = " << sc_time_stamp() << 
			"  A_IN = " << A_IN.read() << 
			"  B_IN = " << B_IN.read() << endl;
		wait();
		wait();
		wait();
		wait();
		wait();


		A_IN.write(65535);
    	B_IN.write(1);
		wait();
		cout << "Time = " << sc_time_stamp() << 
			"  A_IN = " << A_IN.read() << 
			"  B_IN = " << B_IN.read() << endl;
		wait();
		wait();


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
		 
	    sc_stop();
        
    }
        
    SC_CTOR(stim) {
        SC_CTHREAD(stim_process, clock.pos());
    }  
};


SC_MODULE(mon) {
    sc_in< sc_uint<word_length> > Z_OUT;
    sc_in<sc_logic> carry_OUT;
    sc_in_clk clock;
    
    void mon_process(){
        
    	while (1) {
	  		wait();
	  		cout << " * Time = " << sc_time_stamp() << 
		  		"  Z_OUT = " << Z_OUT.read() 
		  		<< " carry_OUT = " << carry_OUT.read() << endl;
    	}

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

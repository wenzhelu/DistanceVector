//
//  main.cpp
//  DistanceVector
//

#include <iostream>
#include <thread>
#include "include/DV.h"
#include "include/UDPSock.h"
#include "include/Changer.h"

using std::thread;

int main(int argc, const char * argv[]) {

	if (argc != 7) {
		printf("Usage:./dv config_file portnumber TTL infinity Period Poison_Reverse(true or false)\n");
		exit(1);
	}

    // initial parameters
        
    DV dv;
    dv.usock = new UDPSock(&dv);
    
    // set up parameters
    dv.init(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
    
    dv.usock->init();

    // make two updaters and spawn 2 threads
    dv.pc = new Changer(&dv);
    
    dv.tt = new thread(&Changer::updateChange, dv.pc);
    dv.tp = new thread(&Changer::periodicChange, dv.pc);
    
    // wait for them
    dv.tp->join();
    dv.tt->join();
    
	return 0;
}

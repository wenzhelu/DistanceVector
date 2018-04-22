//
//  main.cpp
//  DistanceVector
//

#include <iostream>
#include "include/DV.h"
#include "include/UDPSock.h"

int main(int argc, const char * argv[]) {

	if (argc != 7) {
		printf("Usage:./dv config_file portnumber TTL infinity Period Poison_Reverse(true or false)\n");
		exit(1);
	}

    // initial parameters
        
    DV dv;
    dv.usock = new UDPSock(&dv);
    
    dv.init(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);

    // make two updater and spawn 2 threads
    
    // TODO: Changer or updater?
    // periodic updater should print routing table
    // while loop for two updater
    
    dv.tt->join();
    dv.tt->join();
    
	return 0;
}

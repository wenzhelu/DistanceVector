//
//  main.cpp
//  DistanceVector
//

#include <iostream>
#include "include/DV.h"

int main(int argc, const char * argv[]) {
    
	int argCount = 7;

	char config[40];  //length of file name should be less than 40 bytes
	FILE * fp;
	int portNumber;
	int TTL;
	int inf;
	int period;   // period seconds
	bool reverse; // input should  be true or false

	if (argc != argCount)
	{
		printf("Usage:config, portnumber, TTL, infinity, Period, Poison Reverse\n");
		exit(1);
	}
	else
	{
		// initial parameters
		int index = 0;
		while (argv[1][index] != '\0')
		{
			config[index] = argv[1][index];
			index++;
		}
		config[index] = '\0';
		fp = fopen(config, O_RDONLY);

		portNumber = atoi(argv[2]);
		TTL = atoi(argv[3]);
		inf = atoi(argv[4]);
		period = atoi(argv[5]);
		reverse = *argv[6] == 't' ? true : false;

		//call some functions
	}
	return 0;
}

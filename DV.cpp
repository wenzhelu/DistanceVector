//
//  DV.cpp
//  DistanceVector
//
//  Created by Wenzhe Lu on 2018/4/21.
//  Copyright © 2018年 Wenzhe Lu. All rights reserved.
//

#include "include/DV.h"
#include "include/UDPSock.h"
#include <string>

DV::DV(string config, string port, string poison, string TTL, string prd) {
    // init routing table from config and port
	FILE *fp = fopen(config, O_RDONLY);
	char addr[20];
	char cost[4];
	if (fp == NULL)
	{
		printf("config file not found\n");
		exit(1);
	}
	//for each line, addr is the address and cost 
	while (fscanf(fp, "%s %d\n", addr, cost) != EOF)
	{

		uint dest = inet_addr(addr);
		RouterTableEntry line;

		line.ttl = TTL;
		if (cost[0] = 'y')
		{
			//set value for rTable
			line.cost = 1;
			line.next = inet_addr(addr);
			//set value for remoteIP
			usock->remotes.push(addr);
		}
		else
		{
			line.cost = infin;
			line.next = 0;        // 0 for NULL next router
		}
		rTable.insert({ dest,line });
		memset(addr, 0, 20);
		memset(cost, 0, 4);
	}
}

// constructors for DV
void DV::init(string config, string port, string poi) {
    // init routing table from config and port
    
    this->poison = poi.compare("true") == 0;
}

DV::~DV() {
    delete tp;
    delete tt;
    delete usock;
    delete pu;
    delete tu;
}

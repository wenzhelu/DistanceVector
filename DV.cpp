//
//  DV.cpp
//  DistanceVector
//
//  Created by Wenzhe Lu on 2018/4/21.
//  Copyright © 2018年 Wenzhe Lu. All rights reserved.
//

// for local ip addr
#include <sys/types.h>
#include <ifaddrs.h>

#include "include/DV.h"
#include "include/UDPSock.h"
#include <fcntl.h>
#include <string>
#include <vector>

using std::stol;
using std::stoi;


// constructors for DV
void DV::init(string config, string port, string TTL, string infinity, string prd, string poi) {
    // init routing table from config and port
    // init routing table from config and port
    this->port = stoi(port);
    this->poison = (poi.compare("true") == 0);
    this->ttl = (uint) stoi(TTL);
    this->ifinity = (uint) stol(infinity);
    this->period = (uint) stoi(prd);
    
    FILE *fp = fopen(config.data(), "r");
    char address[20];
    char cost[4];
    if (fp == NULL)
    {
        printf("config file not found\n");
        exit(1);
    }
    //for each line, addr is the address and cost
    while (fscanf(fp, "%s %s\n", address, cost) != EOF)
    {
        uint dest = inet_addr(address);
        RouteTableEntry line;
        
        line.ttl = stoi(TTL);
        if (cost[0] == 'y')
        {
            addr tm;

            //set value for rTable
            line.cost = 1;
            line.next = dest;
            
            tm.sin_port = this->port;
            tm.sin_family = AF_INET;
            tm.sin_addr.s_addr = dest;
            
            //set value for remoteIP
            usock->remotes.push_back(tm);
        }
        else
        {
            line.cost = this->ifinity;
            line.next = 0;        // 0 for NULL next router
        }
        rTable.insert({ dest, line });
        memset(address, 0, 20);
        memset(cost, 0, 4);
    }
    // add local ip and set total size
//    tTable.insert({})
}

DV::~DV() {
    delete tp;
    delete tt;
    delete usock;
    delete pu;
    delete tu;
}

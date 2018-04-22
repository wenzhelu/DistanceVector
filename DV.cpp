//
//  DV.cpp
//  DistanceVector
//
//  Created by Wenzhe Lu on 2018/4/21.
//  Copyright © 2018年 Wenzhe Lu. All rights reserved.
//

#include "include/DV.h"
#include "include/UDPSock.h"
#include "include/Changer.h"
#include <fcntl.h>
#include <string>
#include <vector>
#include <iostream>

using std::stol;
using std::stoi;
using std::cout;
using std::endl;

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
    
    fscanf(fp, "%s %s\n", address, cost);
    RouteTableEntry tm;
    tm.cost = 0;
    tm.next = inet_addr(address);
    tm.ttl = ttl;
    rTable.insert({ tm.next, tm });
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
    
    this->vs = (uint) rTable.size();

    buffLen = 8 * this->vs; // each vertex in the network will need 8 byte to communicate infos
}

void DV::printReadBuff() {
    
}

void DV::printSendBuff() {
    // not implement yet
}

// print the routing table
void DV::printRTable() {
    for (auto& p : this->rTable) {
        cout << "dest: " << p.first << ", next: " << p.second.next << ", cost: " << p.second.cost
        << ", ttl: " << p.second.ttl << endl;
    }
}

DV::~DV() {
    delete tp;
    delete tt;
    delete usock;
    delete pc;
}

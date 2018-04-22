//
// Changer.cpp
// periodic update and triggered update
//

#include "include/Changer.h"
#include "include/UDPSock.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <arpa/inet.h>

using std::cout;
using std::endl;
using std::this_thread::sleep_for;
using namespace std::chrono;

// triggered update function
void Changer::updateChange()
{
    // TODO:
    // 1. bugfix
    // 2. print receive info when triggered.
    // 3. update TTL 
    
    while (1) {
        dv->usock->read();
        cout << "=========================INCOMING PACKET=========================" << endl;
        // through UDP to get recBuffer
        bool changeFlag = false;
        uint addr;
        uint cost;
        uint originalCost;
        uint distance;
        uint sendHost;
        int readBufferP = 0;
        int maxRouters = dv->vs;
        
        dv->rTableLock.lock();
        //loop to find the source host
        while (true) {
            addr = *((uint*)(dv->readBuff) + readBufferP);   // first 4 bytes
            cost = *((uint*)(dv->readBuff) + readBufferP + 1);   //second 4 bytes
            if (cost == 0)
            {
                distance = dv->rTable.at(addr).cost = 1;
                sendHost = addr;
                break;
            }
            readBufferP += 2;
        }
        
        cout << "Packet from node: " << DV::uintToIP(sendHost) << endl;
        
        //loop to update
        readBufferP = 0;
        while (readBufferP/2 < maxRouters)
        {
            addr = *((uint*)(dv->readBuff) + readBufferP);   // first 4 bytes
            cost = *((uint*)(dv->readBuff) + readBufferP + 1);   //second 4 bytes
            cout << "IP: " << DV::uintToIP(addr) << ", cost: " << cost << endl;
            RouteTableEntry& p = dv->rTable[addr];
            originalCost = p.cost;
            if (originalCost >= cost + distance)
            {
                p.ttl = dv->ttl;
                p.next = sendHost;
                if (originalCost > cost + distance) {
                    p.cost = cost + distance;
                    changeFlag = true;
                }
            }
            readBufferP += 2;
        }
        
        if (changeFlag) {
            // read routing table into send buffer then send
            uint *tm = (uint*) dv->sendBuff;
            for (auto& p : dv->rTable) {
                *tm++ = p.first;
                *tm++ = p.second.cost;
            }
            dv->usock->write();
        }
        cout << "=========================INCOMING PACKET ENDS=======================\n" << endl;
        dv->rTableLock.unlock();
    }
}

void Changer::periodicChange() {
    while (1) {
        sleep_for(seconds(dv->period));
        dv->rTableLock.lock();
        cout << "=======================ROUTING TABLE==========================" << endl;

        uint *tm = (uint*) dv->sendBuff;
        for(auto it = dv->rTable.begin(); it != dv->rTable.end(); it++) {
            if (it->second.cost != 0) {
                if (it->second.ttl <= dv->period) {
                    it->second.ttl = 0;
                    it->second.cost = dv->ifinity;
                } else {
                    it->second.ttl -= dv->period;
                }
            }
            *tm++ = it->first;
            *tm++ = it->second.cost;
            // print out routing table in periodic update
            cout << "dest: " << DV::uintToIP(it->first) << ", next: " <<  DV::uintToIP(it->second.next) << ", cost: " << it->second.cost << ", ttl: " << it->second.ttl << endl;

        }
        
        cout << "====================ROUTING TABLE ENDS=======================\n" << endl;
        dv->usock->write();
        dv->rTableLock.unlock();
    }
}

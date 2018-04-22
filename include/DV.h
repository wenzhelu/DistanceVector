//
//  DV.h
//  DistanceVector
//

#ifndef DV_h
#define DV_h

// forward declarations for class DV
class UDPSock;
class Changer;

#include <cstddef>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef unsigned int uint;

class RouteTableEntry {
public:
    uint next;
    uint cost;
    uint ttl;
};

using std::vector;
using std::unordered_map;
using std::thread;
using std::mutex;
using std::string;


// class Distance Vector
// store routing table/ routing graph / mutex / UDP socket / Periodic & triggered updater
class DV {
public:
    // components
    Changer *pc;
    UDPSock *usock;
    
    thread *tp;     // thread for periodic updater
    thread *tt;     // thread for triggered updater
    
    mutex rTableLock;      // mutex to synchronize two updaters
    
//    vector<vector<uint>> graph;     // graph
    unordered_map<uint, RouteTableEntry> rTable; // routing table;
    
    bool poison;    // true if use poison reverse
    
    // notice that both ttl and period is in seconds
    uint ttl;
    uint period;
    uint port;
    uint ifinity;
    uint vs;

    char *readBuff;
    char *sendBuff;
    uint buffLen;
    

    DV() {}
    
    void printReadBuff();
    
    void printSendBuff();
    
    void printRTable();
    
    void init(string config, string port, string TTL, string infinity, string prd, string poi);
    
    ~DV();
    
    static char *uintToIP(uint i) {
        struct in_addr tm;
        tm.s_addr = i;
        return inet_ntoa(tm);
    }
};


#endif /* DV_h */

//
//  DV.h
//  DistanceVector
//

#ifndef DV_h
#define DV_h

using namespace std;

// forward declarations for class DV
class UDPSock;
class PUpdater;
class TUpdater;

#include <cstddef>
#include <thread>
#include <mutex>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>

typedef unsigned int uint;
typedef unsigned short ushort;
typedef struct sockaddr_in addr;

class RouteTableEntry {
    addr dest;
    addr next;
    uint cost;
    ushort ttl;
};

// class Distance Vector
// store routing table/ routing graph / mutex / UDP socket / Periodic & triggered updater
class DV {
public:
    // components
    PUpdater *pu;
    TUpdater *tu;
    UDPSock *usock;
    
    thread *tp;     // thread for periodic updater
    thread *tt;     // thread for triggered updater
    
    mutex mut;      // mutex to synchronize two updaters
    
//    vector<vector<uint>> graph;     // graph
    vector<RouteTableEntry> rTable; // routing table;
    
    bool poison;    // true if use poison reverse
    // notice that both ttl and period is in seconds
    int ttl;
    int period;
    
    DV() {}
    
    DV(string config, string port, string poison, string TTL, string prd);
    
    void init(string config, string port, string poison);
    
    ~DV() {
        delete tp;
        delete tt;
        delete usock;
        delete pu;
        delete tu;
    }
};


#endif /* DV_h */

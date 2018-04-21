//
//  UDPSock.h
//  DistanceVector
//
//  Created by Wenzhe Lu on 2018/4/21.
//  Copyright © 2018年 Wenzhe Lu. All rights reserved.
//

#ifndef UDPSock_h
#define UDPSock_h

#include "DV.h"

typedef struct sockaddr_in addr;

class UDPSock {
private:
    DV *dv;
    int socket_fd;
    
    addr local;
    vector<addr> remotes;
    
    // can add socket options later
    
public:
    UDPSock(DV *d);
    
    int init();
    
    // proxy functions
    void read();
    
    void write();
    
    // print received packet for debugging usage
    
    ~UDPSock();
};


#endif /* UDPSock_h */

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

class UDPSock {
private:
    DV *dv
    int socket_fd;
    
    // can add socket options later
    
public:
    UDPSock(DV *d);
    
//    int init(const char *localPort, const char *remoteIp, const char *remotePort);
    
    // proxy functions
    read();
    
    write();
    
    // print received packet for debugging usage
    
    ~UDPSock();
};


#endif /* UDPSock_h */

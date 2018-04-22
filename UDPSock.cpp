//
//  UDPSock.cpp
//  DistanceVector
//
//  Created by Wenzhe Lu on 2018/4/21.
//  Copyright © 2018年 Wenzhe Lu. All rights reserved.
//

#include "include/UDPSock.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

UDPSock::UDPSock(DV *d) : dv(d) {}

int UDPSock::init() {
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        printf("socket setup error\n");
        return -1;
    }
    
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_family = AF_INET;
    local.sin_port = dv->port;
    if (bind(socket_fd, (struct sockaddr *) &local, sizeof(local)) < 0) {
        printf("server binding error\n");
        return -1;
    }
    
    // remotes are assigned in DV's init function
    
//    remote.sin_addr.s_addr = inet_addr(remoteIp);
//    remote.sin_family = AF_INET;
//    remote.sin_port = htons(atoi(remotePort));
    
    return 0;
}

// send routing table information to neighbors
void UDPSock::write() {
    uint *tm = (uint*) dv->sendBuff;
    if (dv->poison) {
        for (auto& remote : remotes) {
            for (auto& p : dv->rTable) {
                *tm++ = p.first;
                *tm++ = p.second.next == remote.sin_addr.s_addr ? dv->ifinity : p.second.cost;
            }
            size_t written = sendto(socket_fd, dv->sendBuff, dv->buffLen, 0, (struct sockaddr *)&remote, sizeof(remote));
            if (written != dv->buffLen) {
                cout << "write socket error" << endl;
            }
        }
    } else {
        for (auto& p : dv->rTable) {
            *tm++ = p.first;
            *tm++ = p.second.cost;
        }
        for (auto& remote : remotes) {
            //        cout << "Sending to IP: " << DV::uintToIP(remote.sin_addr.s_addr) << endl;
            size_t written = sendto(socket_fd, dv->sendBuff, dv->buffLen, 0, (struct sockaddr *)&remote, sizeof(remote));
            if (written != dv->buffLen) {
                cout << "write socket error" << endl;
            }
        }
    }
}

void UDPSock::read() {
    int read = recvfrom(socket_fd, dv->readBuff, dv->buffLen, 0, nullptr, 0);
    if (read != dv->buffLen) {
        cout << "read socket error" << endl;
//        cout << read << endl;
//        cout << errno << endl;
    }
}

UDPSock::~UDPSock() {
    close(socket_fd);
}


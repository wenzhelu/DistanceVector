//
//  DV.cpp
//  DistanceVector
//
//  Created by Wenzhe Lu on 2018/4/21.
//  Copyright © 2018年 Wenzhe Lu. All rights reserved.
//

#include "include/DV.h"
#include <string>

DV::DV(string config, string port, string poison, string TTL, string prd) {
    // init routing table from config and port
}

// constructors for DV
void DV::init(string config, string port, string poi) {
    // init routing table from config and port
    
    this->poison = poi.compare("true") == 0;
}

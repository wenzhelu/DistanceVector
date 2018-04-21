//
//  main.cpp
//  DistanceVector
//

#include <iostream>
#include "include/DV.h"

int main(int argc, const char * argv[]) {
    
    if (argc < 4) {
        cout << "usage: " << endl;
        cout << "./dv config_file port# poison_reverse(true/false) [TTL] [timer_slot]" << endl;
    }
    
    DV dv;
    if (argc > 4) {
        dv.ttl = stoi(argv[4]);
        if (argc > 5) dv.period = stoi(argv[5]);
    }
    
    dv.init(argv[1], argv[2], argv[3]);
    
    return 0;
}

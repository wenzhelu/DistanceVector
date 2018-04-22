#pragma once

#ifndef CHANGER_H
#define CHANGER_H

#include "DV.h"

class Changer
{
public:
    DV *dv;
    Changer(DV *v) : dv(v) {}
    
	void updateChange();
	void periodicChange();
};

#endif

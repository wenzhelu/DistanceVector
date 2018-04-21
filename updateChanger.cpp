
#include "updateChanger.h"

void updateChanger::update()
{
	// through UDP to get recBuffer
	bool changeFlag = false;
	uint addr;
	uint cost;
	uint originalCost;
	uint distance;
	int readBufferP = 0;
	int maxRouters = rTable.size();

	rTableLock.lock();
	//loop to find the source host
	while (readBufferP < maxRouters)
	{
		addr = *((uint*)(dv.readBuff) + readBufferP);   // first 4 bytes
		cost = *((uint*)(dv.readBuff) + readBufferP + 1);   //second 4 bytes
		if (cost == 0)
		{
			distance = dv.rTable.at(addr).cost;
			break;
		}
	}
	
	//loop to update
	while (readBufferP < maxRouters)
	{
		addr = *((uint*)(dv.readBuff) + readBufferP);   // first 4 bytes
		cost = *((uint*)(dv.readBuff) + readBufferP + 1);   //second 4 bytes
		originalCost = dv.rTable.at(addr).cost;
		if (originalCost < cost + distance)
		{
			dv.rTable.at(addr).cost = cost + distance;
			changeFlag = true;
		}
		readBufferP += 2;
	}

	if (changeFlag)
	{
		//call something to send rTable
	}
	rTableLoco.unlock();

}

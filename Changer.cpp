
#include "Changer.h"

void Changer::updateChanger()
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

void Changer::periodicChanger()
{
	//how to use timer
	rTableLock.lock();
	uint passTime;
	uint cost;
	uint newTTL;
	for(auto it = rTable.begin();it!=rTable.end();it++)
	{
		newTTL = *it.ttl - passTime;
		cost = *it.cost;
		if(cost != 0)
		{
			if(newTTL <= 0)
			{
				
			}
			else
			{
				*it.ttl = newTTL;
			}
		}
	}			
	//call something to send 
	rTableLock.unlock();
}

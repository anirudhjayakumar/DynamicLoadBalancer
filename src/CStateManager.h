/*
 * CStateManager.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CSTATEMANAGER_H_
#define CSTATEMANAGER_H_

#include <string>
#include "CCommProxy.h"
#include "CHWMonitor.h"
#include "CJobQueue.h"

struct State {
	double dCPUUtil;
	double dNetwork;
	float  fThrottleVal;
	int    nJobsPending;
	double dSpecTimeCompletion;
	// other HW monitor params
	char *Serialize();
	int DeSerialize(char *buf);
};

class CStateManager {
public:
	CStateManager();
	virtual ~CStateManager();
	int Initialize(const std::string &xml,CCommProxy *proxy,CHWMonitor *monitor,\
			CJobQueue *pJobQueue); //read information policy
	int Start(); //implement thread or timer event to send data to other node
	int UpdateRemoteState(State state);
	int UpdateMyState(State state);
	State GetMyState();
	State GetRemoteState();
private:
	CCommProxy *proxy;
	CHWMonitor *monitor;
	CJobQueue  *pJobQueue;
	int period; //in ms
};

#endif /* CSTATEMANAGER_H_ */

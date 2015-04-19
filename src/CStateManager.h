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
	int Serialize(char **pBuf, int &bufSize);
	int DeSerialize(const char *buf);
};

class CStateManager {
public:
	CStateManager();
	virtual ~CStateManager();
	int Initialize(configInfo *config,CCommProxy *proxy,CHWMonitor *monitor,\
			CJobQueue *pJobQueue); //read information policy
	int Start(); //implement thread or timer event to send data to other node
	int UpdateRemoteState(State &state);
	int UpdateMyState(State state);
	int SendStateToRemote();
	State GetMyState();
	State GetRemoteState();
private:
	CCommProxy *m_pProxy;
	CHWMonitor *m_pMonitor;
	CJobQueue  *m_pJobQueue;
	configInfo *m_pConfig;
};

#endif /* CSTATEMANAGER_H_ */

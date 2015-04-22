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
#include <thread>

struct State {
	int    nJobsPending;
	int    nJobsCompleted;
	float  fThrottleVal;
	double dCPUUtil;
	double dNetwork;
	double dSpecTimeCompletion;
	double timeForOneJob; //in millisecs
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
	// Receive State Info from Remote HWMonitor and Update own data structures
	int UpdateRemoteState(State &state);
	// Receive State Info from Local HWMonitor and Update own data structures
	int UpdateMyState();
	// Gather local state info to be used by some one else
	State GetMyState();
	// Gather remote state info to be used by some one else
	State GetRemoteState();

	int SendStateToRemote();
	void StopThread();
private:
	CCommProxy *m_pProxy;
	CHWMonitor *m_pMonitor;
	CJobQueue  *m_pJobQueue;
	configInfo *m_pConfig;
	int 		period; //in ms
	State 		_localState;	// Storing info for local node
	State 		_remoteState;	// Storing info for remote node
	std::thread *m_thread;
	bool stopThread;
	void Start(); //implement thread or timer event to send data to other node
};

#endif /* CSTATEMANAGER_H_ */

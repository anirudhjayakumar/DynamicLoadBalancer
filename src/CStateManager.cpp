/*
 * CStateManager.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CStateManager.h"
#include "Common.h"

// other HW monitor params
int State::Serialize(char **pBuf, int &bufSize)
{
	bufSize = sizeof(State);
	State *state = new State();
	state->nJobsPending = nJobsPending;
	state->nJobsCompleted = nJobsCompleted;
	state->fThrottleVal = fThrottleVal;
	state->dCPUUtil = dCPUUtil;
	state->dNetwork = dNetwork;
	state->dSpecTimeCompletion = dSpecTimeCompletion;
	state->timeForOneJob = timeForOneJob;
	*pBuf = (char *)state;
	return SUCCESS;
}

int State::DeSerialize(const char *buf)
{
	State *state = (State *)buf;
	nJobsPending = state->nJobsPending;
	nJobsCompleted = state->nJobsCompleted;
	fThrottleVal = state->fThrottleVal;
	dCPUUtil = state->dCPUUtil;
	dNetwork = state->dNetwork;
	dSpecTimeCompletion = state->dSpecTimeCompletion;
	timeForOneJob   = state->timeForOneJob;
	return SUCCESS;
}

void CStateManager::StopThread()
{
	stopThread = true;
}

CStateManager::CStateManager() {
	// TODO Auto-generated constructor stub
	stopThread = false;
}

CStateManager::~CStateManager() {
	// TODO Auto-generated destructor stub
}

int CStateManager::Initialize(configInfo *config,CCommProxy *proxy,CHWMonitor *monitor,\
			CJobQueue *pJobQueue)
{
	//read information policy
	m_pConfig = config;
	m_pProxy	= proxy;
	m_pMonitor = monitor;
	m_pJobQueue = pJobQueue;
	//start thread
	m_thread = new std::thread(&CStateManager::Start, this);
	return SUCCESS;
}
void CStateManager::Start()
{
	//implement thread or timer event to send data to other node
	while(!stopThread)
	{
		m_pProxy->RequestStateFromRemote();
		UpdateMyState();
		std::this_thread::sleep_for(std::chrono::milliseconds(m_pConfig->stateinfo_period));
	}
	return;
}

int CStateManager::UpdateRemoteState(State &state)
{
	_remoteState = state;
	return SUCCESS;
}

int CStateManager::UpdateMyState()
{
	_localState.dCPUUtil 			= m_pMonitor->GetCPUUtil();
	_localState.fThrottleVal 		= m_pMonitor->GetThrottlingValue();
	_localState.nJobsPending 		= m_pJobQueue->GetJobCountPending();
	_localState.nJobsCompleted		= m_pJobQueue->GetJobCountCompleted();
	_localState.dSpecTimeCompletion = _localState.nJobsPending * m_pJobQueue->AverageJobProcTime();
	_localState.timeForOneJob		= m_pJobQueue->GetTimeForOneJob();
	return SUCCESS;
}


State CStateManager::GetMyState()
{
	return _localState;
}

State CStateManager::GetRemoteState()
{
	return _remoteState;
}

int CStateManager::SendStateToRemote()
{
	m_pProxy->SendStateToRemote(&_localState);
	return SUCCESS;
}

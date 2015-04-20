/*
 * CStateManager.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CStateManager.h"
#include "Common.h"


CStateManager::CStateManager() {
	// TODO Auto-generated constructor stub

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
	return SUCCESS;
}
int CStateManager::Start()
{
	//implement thread or timer event to send data to other node
	return SUCCESS;
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

/*
 * CStateManager.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CStateManager.h"
#include "Common.h"

int State::Serialize(char **pBuf,int &bufSize)
{
	return SUCCESS;
}

int State::DeSerialize(const char *buf)
{
	return SUCCESS;
}


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
	return SUCCESS;
}

int CStateManager::UpdateMyState(State state)
{
	return SUCCESS;
}

int CStateManager::SendStateToRemote()
{
	return SUCCESS;
}

State CStateManager::GetMyState()
{
	return State();
}

State CStateManager::GetRemoteState()
{
	return State();
}

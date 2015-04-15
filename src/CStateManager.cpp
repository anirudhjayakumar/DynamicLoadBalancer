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

int CStateManager::Initialize(const std::string &xml,CCommProxy *proxy,CHWMonitor *monitor,\
			CJobQueue *pJobQueue)
{
	//read information policy
	return SUCCESS;
}
int CStateManager::Start()
{
	//implement thread or timer event to send data to other node
	return SUCCESS;
}

int CStateManager::UpdateRemoteState(State state)
{
	return SUCCESS;
}

int CStateManager::UpdateMyState(State state)
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

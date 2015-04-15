/*
 * CCommProxy.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CCommProxy.h"
#include "Common.h"
CCommProxy::CCommProxy() {
	// TODO Auto-generated constructor stub

}

CCommProxy::~CCommProxy() {
	// TODO Auto-generated destructor stub
}


int CCommProxy::Initialize(const std::string &sXML)
{
	return SUCCESS;
}

int CCommProxy::UnInitialize()
{
	return SUCCESS;
}

int CCommProxy::SendJobsToRemote(char *buf)
{
	return SUCCESS;
}

int CCommProxy::RequestJobsFromRemote(int nJobs)
{
	return SUCCESS;
}

int CCommProxy::RequestStateFromRemote()
{
	return SUCCESS;
}

int CCommProxy::SendStatetoRemote(char *pState)
{
	return SUCCESS;
}

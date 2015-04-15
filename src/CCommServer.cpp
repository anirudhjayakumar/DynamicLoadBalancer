/*
 * CCommServer.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CCommServer.h"
#include "Common.h"
CCommServer::CCommServer() {
	// TODO Auto-generated constructor stub

}

CCommServer::~CCommServer() {
	// TODO Auto-generated destructor stub
}

int CCommServer::Initialize(const std::string &sXML)
{
	return SUCCESS;
}

int CCommServer::UnInitialize()
{
	return SUCCESS;
}

int CCommServer::SendJobsToRemote(char *buf)
{
	return SUCCESS;
}

int CCommServer::RequestJobsFromRemote(int nJobs)
{
	return SUCCESS;
}

int CCommServer::RequestStateFromRemote()
{
	return SUCCESS;
}

int CCommServer::SendStatetoRemote(char *pState)
{
	return SUCCESS;
}

/*
 * CTransferManager.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CTransferManager.h"
#include "Common.h"

CTransferManager::CTransferManager() {
	// TODO Auto-generated constructor stub

}

CTransferManager::~CTransferManager() {
	// TODO Auto-generated destructor stub
}

int CTransferManager::Initialize(CJobQueue *pJobQueue, CCommProxy *pProxy)
{
	return SUCCESS;
}

int CTransferManager::SendJobsToRemote(int size)
{
	return SUCCESS;
}

int CTransferManager::RequestJobsFromRemote(int size)
{
	return SUCCESS;
}


int CTransferManager::AddJobsToLocalQueue(std::vector<CJob*> &vJobs)
{
	return SUCCESS;
}

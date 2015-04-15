/*
 * CWorker.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CWorker.h"
#include "Common.h"


CWorker::CWorker() {
	// TODO Auto-generated constructor stub

}

CWorker::~CWorker() {
	// TODO Auto-generated destructor stub
}

int CWorker::Initialize(CJobQueue 	*pJobQueue, CHWMonitor 	*pMonitor)
{
	return SUCCESS;
}

int CWorker::Start()
{
	//async call
	return SUCCESS;
}

int CWorker::UnInitialize()
{
	return SUCCESS;
}

void  CWorker::Run(CJobQueue *pJobQueue,CHWMonitor *pMonitor)
{
	return;
}

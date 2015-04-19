/*
 * CTransferManager.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CTRANSFERMANAGER_H_
#define CTRANSFERMANAGER_H_

#include "CJobQueue.h"
#include "CCommProxy.h"
#include "CJobQueue.h"
class CTransferManager {
public:
	CTransferManager();
	virtual ~CTransferManager();
    int Initialize(CJobQueue *pJobQueue, CCommProxy *pProxy);
    int SendJobsToRemote(int size);
    int RequestJobsFromRemote(int size);
	int AddJobsToLocalQueue(std::vector<CJob*> &vJobs);
private:
	CJobQueue *pJobQueue;
	CCommProxy *pProxy;
};

#endif /* CTRANSFERMANAGER_H_ */

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
    int RequestCompletedJobsFromRemote();
    int SendCompletedJobsToRemote();
    int AddCompletedJobsToLocalQueue(std::vector<CJob*> &vJobs);
    void GetStat();
private:
    int nJobsSend, nJobsReceived;
    CJobQueue *m_pJobQueue;
    CCommProxy *m_pProxy;
};

#endif

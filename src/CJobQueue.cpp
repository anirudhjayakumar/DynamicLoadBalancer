/*
 * CJobQueue.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CJobQueue.h"
#include "Common.h"
#include <iostream>
#include <algorithm>
using namespace std;
CJobQueue::CJobQueue() {
    // TODO Auto-generated constructor stub
    dTotalJobTime = 0;
}

CJobQueue::~CJobQueue() {
    // TODO Auto-generated destructor stub
}

void CJobQueue::IntegrityCheck()
{
    bool fail = false;
    for (auto iter = vJobsCompleted.begin(); iter != vJobsCompleted.end(); ++iter)
    {
        if(!(*iter)->CheckIntegrity())
        {
            cout << "Job fail:" << (*iter)->GetID() << endl;
            fail = true;
        }
    }
    if(!fail)
        cout << "All jobs passed integrity check" << endl;
}

CJob* 		CJobQueue::GetNextJob()
{
    mtx.lock();
    CJob *pJOB = NULL;
    if(vJobsPending.size() > 0)
    {
        pJOB = vJobsPending.front();
        vJobsPending.pop_front();
    }
    mtx.unlock();
    return pJOB;
}

int 			CJobQueue::GetJobCountPending()
{
    return vJobsPending.size();
}

int 			CJobQueue::GetJobCountCompleted()
{
    return vJobsCompleted.size();
}

JobVec 	CJobQueue::SliceChunkFromQueue(int nJobs)
{

    JobVec vecJobs;
    mtx.lock();
    //cout << "Pending: " << vJobsPending.size() << endl;
    //cout << "Begin: " << &vJobsPending.front() << " End: " << &vJobsPending.back() << " nJobs: " << nJobs << " end - nJobs: " << &vJobsPending.back() - nJobs << endl;
    for(unsigned i = vJobsPending.size() - nJobs ; i < vJobsPending.size(); i++) {
        vecJobs.push_back(vJobsPending.at(i));
    }
    vJobsPending.resize(vJobsPending.size() - nJobs);
    mtx.unlock();
    return vecJobs;
}

int 	CJobQueue::AddJobsToQueue(JobVec &vJobs)
{
    cout << "Adding jobs to Queue: ";
    mtx.lock();
    for(auto iter = vJobs.begin(); iter != vJobs.end(); ++iter) {
        cout << (*iter)->GetID() << " ";
        vJobsPending.push_back(*iter);
    }
    mtx.unlock();
    cout << endl;
    return SUCCESS;
}

int 	CJobQueue::AddCompletedJobsToQueue(JobVec &vJobs)
{
    for(auto iter = vJobs.begin(); iter != vJobs.end(); ++iter)
        vJobsCompleted.push_back(*iter);
    return SUCCESS;
}

int 	CJobQueue::ListCompletedJobs()
{
    cout << "List of completed Jobs: ";
    for (auto iter = vJobsCompleted.begin(); iter != vJobsCompleted.end(); ++iter)
    {
        cout << (*iter)->GetID() << ",";
    }
    return SUCCESS;
}

JobVec		CJobQueue::GetCompletedJobs()
{
    return vJobsCompleted;
}

void CJobQueue::SetTimeForOneJob(double dTime)
{
    timeForOneJob = dTime;
}

double CJobQueue::GetTimeForOneJob()
{
    return timeForOneJob;
}

int 	CJobQueue::AddCompletedJob(CJob *job)
{
    mtx.lock(); //this lock is necessary when there are multiple workers
    vJobsCompleted.push_back(job);
    mtx.unlock();
    return SUCCESS;
}


double			CJobQueue::GetLastJobTime()
{
    return dLastJobTime;
}

double 			CJobQueue::AverageJobProcTime()
{
    mtx.lock();
    double avg = dTotalJobTime/vJobsCompleted.size();
    mtx.unlock();
    return avg;
}

int 			CJobQueue::AddNewJobTime(double dTime)
{
    mtx.lock();
    dLastJobTime = dTime;
    dTotalJobTime+=dTime;
    mtx.unlock();
    return SUCCESS;
}

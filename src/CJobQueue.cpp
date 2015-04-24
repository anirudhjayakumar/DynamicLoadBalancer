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

CJob* 		CJobQueue::GetNextJob()
{
	//mtx.lock();
	CJob *pJOB = NULL;
	if(vJobsPending.size() > 0)
	{
		pJOB = vJobsPending.front();
		vJobsPending.pop_front();
	}
	//mtx.unlock();
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
	//mtx.lock();
	copy(vJobsPending.begin() + (vJobsPending.size() - nJobs),vJobsPending.end(),vecJobs.begin());
	vJobsPending.erase(vJobsPending.begin() + (vJobsPending.size() - nJobs),vJobsPending.end());
	//mtx.unlock();
	return vecJobs;
}

int 	CJobQueue::AddJobsToQueue(JobVec &vJobs)
{
	//mtx.lock();
	vJobsPending.insert (vJobsPending.end(),vJobs.begin(),vJobs.end());
	//mtx.unlock();
	return SUCCESS;
}

int 	CJobQueue::AddCompletedJobsToQueue(JobVec &vJobs)
{
	vJobsCompleted.insert (vJobsCompleted.end(),vJobs.begin(),vJobs.end());
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
	//mtx.lock(); //this lock is necessary when there are multiple workers
	vJobsCompleted.push_back(job);
	//mtx.unlock();
	return SUCCESS;
}


double			CJobQueue::GetLastJobTime()
{
	return dLastJobTime;
}

double 			CJobQueue::AverageJobProcTime()
{
	//mtx.lock();
	double avg = dTotalJobTime/vJobsCompleted.size();
	//mtx.unlock();
	return avg;
}

int 			CJobQueue::AddNewJobTime(double dTime)
{
	//mtx.lock();
	dLastJobTime = dTime;
	dTotalJobTime+=dTime;
	//mtx.unlock();
	return SUCCESS;
}

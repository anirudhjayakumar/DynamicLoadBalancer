/*
 * CJobQueue.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CJobQueue.h"
#include "Common.h"

#include <algorithm>
CJobQueue::CJobQueue() {
	// TODO Auto-generated constructor stub
	dTotalJobTime = 0;
}

CJobQueue::~CJobQueue() {
	// TODO Auto-generated destructor stub
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
	copy(vJobsPending.begin() + (vJobsPending.size() - nJobs),vJobsPending.end(),vecJobs.begin());
	vJobsPending.erase(vJobsPending.begin() + (vJobsPending.size() - nJobs),vJobsPending.end());
	mtx.unlock();
	return vecJobs;
}

int 	CJobQueue::AddJobsToQueue(JobVec vJobs)
{
	mtx.lock();
	vJobsPending.insert (vJobsPending.end(),vJobs.begin(),vJobs.end());
	mtx.unlock();
	return SUCCESS;
}

int 	CJobQueue::AddCompletedJob(CJob *job)
{
	vJobsCompleted.push_back(job);
	return SUCCESS;
}


double			CJobQueue::GetLastJobTime()
{
	return dLastJobTime;
}

double 			CJobQueue::AverageJobProcTime()
{
	return dTotalJobTime/vJobsCompleted.size();
}

int 			CJobQueue::AddNewJobTime(double dTime)
{
	dLastJobTime = dTime
	dTotalJobTime+=dTime;
	return SUCCESS;
}

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
	for (auto iter = vJobsCompleted.begin(); iter != vJobsCompleted.end(); ++iter)
        {
                cout << (*iter)->GetID() << ": " << (*iter)->CheckIntegrity() << "  ";
        }
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
	//cout << "Pending: " << vJobsPending.size() << endl;
	//cout << "Begin: " << &vJobsPending.front() << " End: " << &vJobsPending.back() << " nJobs: " << nJobs << " end - nJobs: " << &vJobsPending.back() - nJobs << endl;
	//copy(vJobsPending.begin() + (vJobsPending.size() - nJobs),vJobsPending.end(),vecJobs.begin());
        for(unsigned i = vJobsPending.size() - nJobs ; i < vJobsPending.size(); i++) {
            vecJobs.push_back(vJobsPending.at(i));
        }
        vJobsPending.resize(vJobsPending.size() - nJobs);
        //copy(vJobsPending.rbegin(), vJobsPending.rbegin() - nJobs, vecJobs.begin());
        //vJobsPending.erase(vJobsPending.end(), vJobsPending.end() + nJobs);
	//vJobsPending.erase(vJobsPending.begin() + (vJobsPending.size() - nJobs),vJobsPending.end());
	//mtx.unlock();
	return vecJobs;
}

int 	CJobQueue::AddJobsToQueue(JobVec &vJobs)
{
	//mtx.lock();
        cout << "Adding jobs to Queue: ";
	for(auto iter = vJobs.begin(); iter != vJobs.end(); ++iter) {
                cout << (*iter)->GetID() << ",";
		vJobsPending.push_back(*iter);
        }
	//mtx.unlock();
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

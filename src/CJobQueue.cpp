/*
 * CJobQueue.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CJobQueue.h"
#include "Common.h"
CJobQueue::CJobQueue() {
	// TODO Auto-generated constructor stub

}

CJobQueue::~CJobQueue() {
	// TODO Auto-generated destructor stub
}

CJob* 		CJobQueue::GetNextJob()
{
	return NULL;
}

int 			CJobQueue::GetJobCountPending()
{
	return SUCCESS;
}

int 			CJobQueue::GetJobCountCompleted()
{
	return SUCCESS;
}

JobVec 			CJobQueue::SliceChunkFromQueue(int nJobs)
{
	return JobVec();
}

int 			CJobQueue::AddJobsToQueue(JobVec vJobs)
{
	return SUCCESS;
}

double 			CJobQueue::AverageJobProcTime()
{
	return SUCCESS;
}

int 			CJobQueue::AddNewJobTime(double dTime)
{
	return SUCCESS;
}

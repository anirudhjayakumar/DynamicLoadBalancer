/*
 * CWorker.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CWorker.h"
#include "Common.h"
#include<time.h>

CWorker::CWorker() {
	// TODO Auto-generated constructor stub

}

CWorker::~CWorker() {
	// TODO Auto-generated destructor stub
}

int CWorker::Initialize(CJobQueue 	*jobQueue, CHWMonitor 	*monitor)
{
	pJobQueue = jobQueue;
	pMonitor = monitor;
	p_thread = new std::thread(&CWorker::Start, this);
	return SUCCESS;
}

int CWorker::Start()
{
	//execute two times and calculate average
	int count = 0;
	long totaltime = 0;
	double avgTime = 0;
	struct timeval start, end;
	long mtime, seconds, useconds;
	double sleep_time = 0;
	while (count < 2)
	{
		CJob *pJob = pJobQueue->GetNextJob();
		if(pJob == NULL)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			continue;
		}
		gettimeofday(&start, NULL);
		pJob->ExecJob();
		gettimeofday(&end, NULL);
		seconds  = end.tv_sec  - start.tv_sec;
		useconds = end.tv_usec - start.tv_usec;
		mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
		totaltime+=mtime;
		pJobQueue->AddNewJobTime(double(mtime));
		pJobQueue->AddCompletedJob(pJob);
		count++;
	}
	avgTime = (double)totaltime/2;

	while(1){
		CJob *pJob = pJobQueue->GetNextJob();
		if(pJob == NULL)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			continue;
		}
		gettimeofday(&start, NULL);
		pJob->ExecJob();
		sleep_time = ((1/pMonitor->GetThrottlingValue()) - 1) * avgTime;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
		gettimeofday(&end, NULL);
		seconds  = end.tv_sec  - start.tv_sec;
		useconds = end.tv_usec - start.tv_usec;
		mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
		pJobQueue->AddNewJobTime(double(mtime));
		pJobQueue->AddCompletedJob(pJob);
	}
	//async call
	return SUCCESS;
}



int CWorker::UnInitialize()
{
	return SUCCESS;
}


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
	p_thread = new std::thread(&CWorker::Start(), this);
	return SUCCESS;
}

double CWorker::CalculateSleepTime(){
	clock_t start = clock();
	CJob *j = pJobQueue->GetNextJob();
	for( int j=0; j < 1000; j++){
		*(j->buf) += 1.111111;
	}
	clock_t end = clock();
	return (double)(end - start)/CLOCKS_PER_SEC;
}
int CWorker::Start()
{
	double avg_time = CWorker::CalculateSleepTime();
	float throttlingValue = pMonitor->GetThrottlingValue();
	float sleep_time = ((1/throttlingValue) - 1) * avg_time;
	while(1){
		CWorker::Run();
		//sleep depending on throttle
		std::this_thread::sleep_for(std::chrono::seconds(sleep_time));
	}
	//async call
	return SUCCESS;
}

int CWorker::UnInitialize()
{
	return SUCCESS;
}

void  CWorker::Run()
{
	CJob *j = pJobQueue->GetNextJob();
	for( int j=0; j < 1000; j++){
		*(j->buf) += 1.111111;
	}
	pJobQueue->AddCompletedJob(j);
	return;
}

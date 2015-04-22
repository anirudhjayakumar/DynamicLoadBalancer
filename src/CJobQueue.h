/*
 * CJobQueue.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CJOBQUEUE_H_
#define CJOBQUEUE_H_

#include "CJob.h"
#include <queue>
#include <mutex>

class CJobQueue {
private:
	JobQ vJobsPending;
	JobVec vJobsCompleted;
	double dTotalJobTime;
	std::mutex mtx;
	double dLastJobTime;
	double timeForOneJob;
	// mutex also needs to be included
public:
	CJobQueue();
	virtual ~CJobQueue();

	CJob* 			GetNextJob();
	int 			GetJobCountPending();
	int 			GetJobCountCompleted();
	JobVec 			SliceChunkFromQueue(int nJobs);
	int 			AddJobsToQueue(JobVec vJobs);
	double 			AverageJobProcTime();
	int 			AddNewJobTime(double dTime);
	int 			AddCompletedJob(CJob *job);
	double			GetLastJobTime();
	void 			SetTimeForOneJob(double);
	double 			GetTimeForOneJob();
};

#endif /* CJOBQUEUE_H_ */

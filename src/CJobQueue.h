/*
 * CJobQueue.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CJOBQUEUE_H_
#define CJOBQUEUE_H_

#include "CJob.h"
#include <vector>

class CJobQueue {
private:
	JobVec vJobsPending;
	JobVec vJobsCompleted;
	double dTotalJobTime;
	int    nJobsCompleted;
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
};

#endif /* CJOBQUEUE_H_ */

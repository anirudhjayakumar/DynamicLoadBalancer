/*
 * CWorker.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CWORKER_H_
#define CWORKER_H_

#include "CJobQueue.h"
#include "CHWMonitor.h"
#include <thread> // c++11 can use boost also

typedef std::thread ThreadType;

class CWorker {
public:
	CWorker();
	virtual ~CWorker();
	int Initialize(CJobQueue 	*pJobQueue, CHWMonitor 	*pMonitor);
	int Start(); //async call
	int UnInitialize();
private:
	CJobQueue 	*pJobQueue;
	CHWMonitor 	*pMonitor;
	ThreadType *pThread;
	void  Run(CJobQueue *pJobQueue,CHWMonitor *pMonitor);

};

#endif /* CWORKER_H_ */

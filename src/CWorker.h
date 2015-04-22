/*
 * CWorker.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CWORKER_H_
#define CWORKER_H_

#include<time.h>
#include "CJobQueue.h"
#include "CHWMonitor.h"
#include <thread> // c++11 can use boost also

typedef std::thread ThreadType;

class CWorker {
public:
	CWorker();
	virtual ~CWorker();
	int Initialize(CJobQueue 	*pJobQueue, CHWMonitor 	*pMonitor);
	int UnInitialize();
	void StopThread();
private:
	CJobQueue 	*pJobQueue;
	CHWMonitor 	*pMonitor;
	std::thread *p_thread;
	int  Start();
	bool stopThread;


};

#endif /* CWORKER_H_ */

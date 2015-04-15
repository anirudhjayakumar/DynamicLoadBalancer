/*
 * CHWMonitor.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CHWMONITOR_H_
#define CHWMONITOR_H_

//thread safe: worker tread and comm thread
class CHWMonitor {
public:
	CHWMonitor();
	virtual ~CHWMonitor();
	// either start thread or callback timer
	int StartMonitoring();
	double GetCPUUtil();
	double GetNetwork();
	float  GetThrottlingValue();
	void   SetCPUUtil();
	void   SetNetwork();
	void   SetThrottlingValue();
private:
	double dCPUUtil;
	double dNetwork;
	float  dThrotling;
	// add relevent stuff here
};

#endif /* CHWMONITOR_H_ */
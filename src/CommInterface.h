/*
 * CommInterface.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef COMMINTERFACE_H_
#define COMMINTERFACE_H_

#include <string>

class ICommInterface
{
public:
	virtual ~ICommInterface() {}
	virtual int Initialize(const std::string &sXML) = 0;
	virtual int UnInitialize() = 0;
	virtual int SendJobsToRemote(char *buf) = 0;
	virtual int RequestJobsFromRemote(int nJobs) = 0;
	virtual int RequestStateFromRemote() = 0;
	virtual int SendStatetoRemote(char *pState) = 0;
	// will need synchronous functions for communicating with UI
};

#endif /* COMMINTERFACE_H_ */

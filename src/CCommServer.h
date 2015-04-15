/*
 * CCommServer.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CCOMMSERVER_H_
#define CCOMMSERVER_H_

#include "CommInterface.h"

class CCommServer: public ICommInterface {
public:
	CCommServer();
	virtual ~CCommServer();
	int Initialize(const std::string &sXML);
	int UnInitialize();
	int SendJobsToRemote(char *buf);
	int RequestJobsFromRemote(int nJobs);
	int RequestStateFromRemote();
	int SendStatetoRemote(char *pState);
};

#endif /* CCOMMSERVER_H_ */

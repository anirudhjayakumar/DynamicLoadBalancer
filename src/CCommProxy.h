/*
 * CCommProxy.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CCOMMPROXY_H_
#define CCOMMPROXY_H_
#include "CommInterface.h"

class CCommProxy: public ICommInterface {
public:
	CCommProxy();
	virtual ~CCommProxy();
	int Initialize(const std::string &sXML);
	int UnInitialize();
	int SendJobsToRemote(char *buf);
	int RequestJobsFromRemote(int nJobs);
	int RequestStateFromRemote();
	int SendStatetoRemote(char *pState);
};

#endif /* CCOMMPROXY_H_ */

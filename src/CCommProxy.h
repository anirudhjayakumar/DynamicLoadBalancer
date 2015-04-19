/*
 * CCommProxy.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CCOMMPROXY_H_
#define CCOMMPROXY_H_
#include <string>
#include <vector>
#include "Common.h"
class CJob;
namespace Comm
{
class DynLBServerClient;
};

struct State;
class CCommProxy {
private:
    Comm::DynLBServerClient *pClient;
    configInfo *m_pConfig;
public:
	CCommProxy();
	virtual ~CCommProxy();
	int Initialize(configInfo *config);
	int UnInitialize();
	int SendJobsToRemote(std::vector<CJob*> &vJobs);
	int RequestJobsFromRemote(int nJobs);
	int RequestStateFromRemote();
	int SendStatetoRemote(State *state);
};

#endif /* CCOMMPROXY_H_ */

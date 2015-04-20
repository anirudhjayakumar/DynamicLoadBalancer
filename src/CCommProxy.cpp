/*
 * CCommProxy.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <fstream>
#include "DynLBServer.h"
#include "CCommProxy.h"
#include "Common.h"
#include "CJob.h"
#include "CStateManager.h"
using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Comm;



CCommProxy::CCommProxy() {
	// TODO Auto-generated constructor stub
	pClient = NULL;
}

CCommProxy::~CCommProxy() {
	// TODO Auto-generated destructor stub
}


int CCommProxy::Initialize(configInfo *config)
{
	m_pConfig = config;
	string sIp = m_pConfig->nodeInfo[m_pConfig->remoteNodeId].ip;
	int port = m_pConfig->nodeInfo[m_pConfig->remoteNodeId].port;
	TSocket *tsock = new TSocket(sIp.c_str(), port);
	tsock->setConnTimeout(20000); //20secs
	boost::shared_ptr<TTransport> socket(tsock);
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	pClient = new DynLBServerClient(protocol);
	return SUCCESS;
}

int CCommProxy::UnInitialize()
{
	delete pClient;
	return SUCCESS;
}

int CCommProxy::SendJobsToRemote(vector<CJob*> &vJobs)
{
	CJob *pJob = NULL;
	char *dataBuf = NULL;
	int  bufSize = 0;
	vector<string> vSerializedJobs;
	for(vector<CJob*>::iterator iter = vJobs.begin(); iter != vJobs.end(); ++iter)
	{
		pJob = *iter;
		pJob->Serialize(&dataBuf,bufSize);
		string strData(dataBuf,bufSize);
		vSerializedJobs.push_back(strData);
		delete dataBuf;
	}
	pClient->SendJobsToRemote(vSerializedJobs.size(),vSerializedJobs);
	return SUCCESS;
}

int CCommProxy::RequestJobsFromRemote(int nJobs)
{
	pClient->RequestJobsFromRemote(nJobs);
	return SUCCESS;
}

int CCommProxy::RequestStateFromRemote()
{	
	pClient->RequestStateFromRemote();
	return SUCCESS;
}

int CCommProxy::SendStateToRemote(State *state)
{
	int nBufSize = 0;
	char *pBuf = NULL;
	state->Serialize(&pBuf,nBufSize);
    string strData(pBuf,nBufSize);
	pClient->SendStateToRemote(strData);
	delete pBuf;
	return SUCCESS;
}

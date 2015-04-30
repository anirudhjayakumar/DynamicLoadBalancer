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
#include <iostream>
using namespace std;
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
	cout << "Trying to connect to " << sIp  << ":" << port << endl;
	TSocket *tsock = new TSocket(sIp.c_str(), port);
	tsock->setConnTimeout(20000); //20secs
	boost::shared_ptr<TTransport> socket(tsock);
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	pClient = new DynLBServerClient(protocol);
	transport->open();
	return SUCCESS;
}

int CCommProxy::UnInitialize()
{
	
	delete pClient;
	return SUCCESS;
}


int CCommProxy::RequestCompletedJobsFromRemote()
{
	pClient->RequestCompletedJobsFromRemote();
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
#ifdef COMPRESS
                vector<uint8_t> compress_out;
                compress_buffer(dataBuf,bufSize,compress_out);
                delete dataBuf; //delete original bufffer
                dataBuf = (char *)&compress_out[0]; //address of the vec buffer
                bufSize = compress_out.size(); //compressed size
                string strData(dataBuf,bufSize);
                vSerializedJobs.push_back(strData);
#else
		string strData(dataBuf,bufSize);
		vSerializedJobs.push_back(strData);
		delete dataBuf;
#endif
                delete pJob;
	}
	pClient->SendJobsToRemote(vSerializedJobs.size(),vSerializedJobs);
	return SUCCESS;
}


int CCommProxy::SendCompletedJobsToRemote(std::vector<CJob*> &vJobs)
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
	pClient->SendCompletedJobsToRemote(vSerializedJobs.size(),vSerializedJobs);
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
	//cout << "Buffersize" << nBufSize << " String size=" << strData.size() << endl;
	pClient->SendStateToRemote(strData);
	delete pBuf;
	return SUCCESS;
}

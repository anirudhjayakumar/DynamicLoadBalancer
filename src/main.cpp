/*
 * main.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "Common.h"
#include <boost/lexical_cast.hpp>
#include "CJob.h"
#include "CWorker.h"
#include "CAdaptor.h"
#include "CCommProxy.h"
#include "CJobQueue.h"
#include "CCommServer.h"
#include "CStateManager.h"
#include "CTransferManager.h"
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Usage: ./mp4 <node ID> <config_xml>" << endl;
		return 1;
	}

	int node = boost::lexical_cast<int>(argv[1]);
	string filePath = argv[2];
        cout << "Starting process " << node << ". Config file:"  << filePath << endl;
	// config accessor struct

	configInfo config_;
	config_.myNodeId = node;
	config_.remoteNodeId = (node+1)%2;
	cout << "Loading configuration..." << endl;
	config_.load(filePath);
        cout << "============================" << endl;
	cout << "NodeID: " << config_.myNodeId << " RemoteID: " << config_.remoteNodeId << endl;
	cout << config_.print() << endl;
        cout << "============================" << endl;
	//create all objects
	cout << "Instantiating components.." << endl;
	CJobQueue 			*pJobQ 			= new CJobQueue();
	CWorker 			*pWorker		= new CWorker();
	CHWMonitor 			*pMonitor 		= new CHWMonitor();
	CStateManager 		*pStateMgr 		= new CStateManager();
	CTransferManager 	*pTransferMgr 	= new CTransferManager();
	CAdaptor			*pAdaptor		= new CAdaptor();

        cout << "Starting communication server" << endl;
	//commserver start and init
	CCommServer commServer;
	commServer.Init(&config_,pTransferMgr,pStateMgr); //starts the commserver
       
	//commproxy start and init
	
        
	// bootstrap phase
        cout << "Bootstrap phase starts" << endl;
	cout << "Generating workload" << endl;
	JobVec vJobs_local;
	JobVec vJobs;
	if(config_.myNodeId == 0)
	{
		int nJobs = config_.nJobs;
		int nWorkload = config_.workloadSize;
		int sizePerJob = nWorkload/nJobs;
		cout  << "Size per job " << sizePerJob << endl;
		for (int count = 0; count < nJobs/2; ++count)
		{
			double *pbuf = new double[sizePerJob];
			memset(pbuf,0,sizePerJob*sizeof(double));
			CJob *pJob = new CJob(count,sizePerJob,pbuf);
			vJobs.push_back(pJob);
		}
		//sending half of the workload to remote
		cout << "Sending " << nJobs/2 <<  " jobs to remote" << endl;

		for (int count = 0; count < nJobs/2; ++count)
		for (int count = nJobs/2; count < nJobs; ++count)
		{
			double *pbuf = new double[sizePerJob];
			memset(pbuf,0,sizePerJob*sizeof(double));
			CJob *pJob = new CJob(count,sizePerJob,pbuf);
			vJobs_local.push_back(pJob);
		}
		cout << "Added " << nJobs/2 <<  " jobs to local queue" << endl;
	}

	cout << endl << "press ENTER when process " << config_.remoteNodeId  << " is ready" << endl;
	getchar();
	cout << "Starting proxy to the remote server" << endl;
        CCommProxy commProxy;
	commProxy.Initialize(&config_);
	commProxy.SendJobsToRemote(vJobs);
	pJobQ->AddJobsToQueue(vJobs_local);
//init all objects
	pWorker->Initialize(pJobQ,pMonitor);
	pMonitor->Initialize(&config_);
	pStateMgr->Initialize(&config_,&commProxy,pMonitor,pJobQ);
	pTransferMgr->Initialize(pJobQ,&commProxy);
	pAdaptor->Initialize(pStateMgr,pTransferMgr,&config_);
	//Wait for commserver
	commServer.WaitServer();
	// uninit all objects
	// delete all objects
	return SUCCESS;
}



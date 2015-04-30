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
#include <cstdlib>
#include "CStateManager.h"
#include "CTransferManager.h"
#include <iostream>
#include <unistd.h>
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
        CCommProxy commProxy;
	pTransferMgr->Initialize(pJobQ,&commProxy);
	CCommServer commServer;
	commServer.Init(&config_,pTransferMgr,pStateMgr); //starts the commserver
       
	//commproxy start and init
	
        
	// bootstrap phase
        cout << "============================" << endl;
        cout << "Bootstrap phase starts" << endl;
	JobVec vJobs_local;
	JobVec vJobs;
	int nJobs = config_.nJobs;
	int nWorkload = config_.workloadSize;
	int sizePerJob = nWorkload/nJobs;
	if(config_.myNodeId == 0)
	{
	        cout << "Generating workload" << endl;
		cout  << "Size per job " << sizePerJob << endl;
		for (int count = 0; count < nJobs/2; ++count)
		{
			double *pbuf = new double[sizePerJob];
			memset(pbuf,0,sizePerJob*sizeof(double));
			CJob *pJob = new CJob(count,sizePerJob,pbuf);
			vJobs.push_back(pJob);
		}
		//sending half of the workload to remote

		for (int count = nJobs/2; count < nJobs; ++count)
		{
			double *pbuf = new double[sizePerJob];
			memset(pbuf,0,sizePerJob*sizeof(double));
			CJob *pJob = new CJob(count,sizePerJob,pbuf);
			vJobs_local.push_back(pJob);
		}
	}

        cout << "============================" << endl;
	cout << endl << "press ENTER when process " << config_.remoteNodeId  << " is ready" << endl;
	getchar();
	cout << "Starting proxy to the remote server" << endl;
        commProxy.Initialize(&config_);
	if(config_.myNodeId == 0) {
                //sleep(2); // so that the other node can be unpaused
                cout << "============================" << endl;
		commProxy.SendJobsToRemote(vJobs);
		cout << "Sending " << nJobs/2 <<  " jobs to remote" << endl;
		pJobQ->AddJobsToQueue(vJobs_local);
		cout << "Added " << nJobs/2 <<  " jobs to local queue" << endl;
                cout << "============================" << endl;
	}
	//init all objects
	pWorker->Initialize(pJobQ,pMonitor,&config_);
	pMonitor->Initialize(&config_);
	pStateMgr->Initialize(&config_,&commProxy,pMonitor,pJobQ);
	pAdaptor->Initialize(pStateMgr,pTransferMgr,&config_);
	//Wait for commserver
	commServer.WaitServer();
	// uninit all objects
	// delete all objects
	return SUCCESS;
}



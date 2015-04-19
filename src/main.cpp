/*
 * main.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "Common.h"
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "Usage: ./mp4 <node ID> <config_xml>" << endl;
		return 1;
	}

	int node = lexical_cast<int>(argv[1]);
	string filePath = argv[2];

	// config accessor struct
	configInfo config_;
	config_.myNodeId = node;
	config_.remoteNodeId = (node+1)%2;
	config_.load(filePath);

	//create all objects
	CJobQueue 			*pJobQ 			= new CJobQueue();
	CWorker 			*pWorker		= new CWorker();
	CHWMonitor 			*pMonitor 		= new CHWMonitor();
	CStateManager 		*pStateMgr 		= new CStateManager();
	CTransferManager 	*pTransferMgr 	= new CTransferManager();
	CAdaptor			*pAdaptor		= new CAdaptor();


	//commserver start and init
	CCommServer commServer;
	commServer.Init(&config_,pTransferMgr,pStateMgr); //starts the commserver

	//commproxy start and init
	CCommProxy commProxy;
	commProxy.Initialize(&config_);


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



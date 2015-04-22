/*
 * CAdapter.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CADAPTOR_H_
#define CADAPTOR_H_

#include "CStateManager.h"
#include "CTransferManager.h"
#include <string>
#include <thread>

enum ETransferPolicy
{
	e_SenderInitialted,
	e_ReceiverInitiated,
	e_Symmetric
};

enum ETransferAlgo
{
	e_JobCount,
	e_JobCompletion,
	e_Advanced
};

class CAdaptor {
public:
	CAdaptor();
	virtual ~CAdaptor();
	int Initialize(CStateManager *pStateManager, CTransferManager *pTransferManager,configInfo *config);
	void Start(); // thread or event timers
	void StopThread();
private:
	int TransferPolicy();
	int TransferPolicyBasic();
	int TransferPolicy();
	configInfo *m_pConfig;
	CStateManager *m_pStateManager;
	CTransferManager *m_pTransferManager;
	bool stopThread;
	ETransferPolicy ePolicy;
	ETransferAlgo   eAlgo;
	std::thread *m_thread;
};

#endif /* CADAPTOR_H_ */

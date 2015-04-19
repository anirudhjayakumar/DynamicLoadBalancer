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

enum ETransferPolicy
{
	e_SenderInitialted,
	e_ReceiverInitiated,
	e_Symmetric
};

class CAdaptor {
public:
	CAdaptor();
	virtual ~CAdaptor();
	int Initialize(CStateManager *pStateManager, CTransferManager *pTransferManager,configInfo *config);
	int Start(); // thread or event timers
private:
	int TransferPolicy(ETransferPolicy ePolicy);
	int SelectionPolicy(ETransferPolicy ePolicy, State remote, State local); //return no of jobs
	configInfo *m_pConfig;
	CStateManager *m_pStateManager;
	CTransferManager *m_pTransferManager;
};

#endif /* CADAPTOR_H_ */

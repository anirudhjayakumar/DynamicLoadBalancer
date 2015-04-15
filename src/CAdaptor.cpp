/*
 * CAdapter.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CAdaptor.h"
#include "Common.h"


CAdaptor::CAdaptor() {
	// TODO Auto-generated constructor stub

}

CAdaptor::~CAdaptor() {
	// TODO Auto-generated destructor stub
}


int CAdaptor::Initialize(CStateManager *pStateManager, CTransferManager *pTransferManager,const std::string &sXml)
{
	return SUCCESS;
}

int CAdaptor::Start() // thread or event timers
{
	return SUCCESS;
}

int CAdaptor::TransferPolicy(ETransferPolicy ePolicy)
{
	return SUCCESS;
}

int CAdaptor::SelectionPolicy(ETransferPolicy ePolicy, State remote, State local)
{
	return SUCCESS;
}

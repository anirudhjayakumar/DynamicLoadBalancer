#ifndef COMMSERVER_H_
#define COMMSERVER_H_

#include <thread>
class CStateManager;
class CTransferManager;
class CCommServer
{
private:
	std::thread *m_thread;
    CTransferManager *transferMgr;
	CStateManager    *stateMgr;
	void Start();
public:
	CCommServer();
	virtual ~CCommServer();
	void Init(/* xml struct*/CTransferManager *transfer,CStateManager *stateMgr);
	int WaitServer();
	int UnInit();
    CStateManager *GetStateMgr();
	CTransferManager *GetTrsfrMgr();
};

#endif

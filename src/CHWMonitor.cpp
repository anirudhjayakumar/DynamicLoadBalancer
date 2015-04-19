/*
 * CHWMonitor.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CHWMonitor.h"
#include "Common.h"
CHWMonitor::CHWMonitor() {
	// TODO Auto-generated constructor stub

}

CHWMonitor::~CHWMonitor() {
	// TODO Auto-generated destructor stub
}

int		CHWMonitor::Initialize(configInfo *info)
{
	m_pConfig = info;
	return SUCCESS;
}

int 	CHWMonitor::StartMonitoring()
{
	return SUCCESS;
}

double 	CHWMonitor::GetCPUUtil()
{
	return SUCCESS;
}

double 	CHWMonitor::GetNetwork()
{
	return SUCCESS;
}

float  	CHWMonitor::GetThrottlingValue()
{
	return SUCCESS;
}

void   	CHWMonitor::SetCPUUtil()
{
	return;
}

void   	CHWMonitor::SetNetwork()
{
	return;
}

void   	CHWMonitor::SetThrottlingValue()
{
	return;
}

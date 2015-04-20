/*
 * CHWMonitor.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CHWMonitor.h"
#include "Common.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string.hpp>

using namespace std;
using boost::is_any_of;

CHWMonitor::CHWMonitor() {
	// TODO Auto-generated constructor stub

}

CHWMonitor::~CHWMonitor() {
	// TODO Auto-generated destructor stub
}

int		CHWMonitor::Initialize(configInfo *info)
{
	m_pConfig = info;
	m_thread = new std::thread(&CHWMonitor::StartMonitoring, this);
	return SUCCESS;
}

void 	CHWMonitor::StartMonitoring()
{
	for(;;)
	{
		SetCPUUtil();
		SetNetwork();
		SetThrottlingValue();
		std::this_thread::sleep_for(std::chrono::milliseconds(m_pConfig->monitor_period));
	}
	return;

}

double 	CHWMonitor::GetCPUUtil()
{
	return dCPUUtil;
}

double 	CHWMonitor::GetNetwork()
{
	return SUCCESS;
}

float  	CHWMonitor::GetThrottlingValue()
{
	return dThrotling;
}

int   	CHWMonitor::SetCPUUtil()
{
	string cpuUtilization;
	vector<string> strVec;
	ifstream stat_file("/proc/stat");
	if(!stat_file){
		cout << "Connot open /proc/stat" << endl;
		return FAIL;
	}
	else {
		cout << "Parsing stat file for CPU info" << endl;
	}
	while(getline(stat_file, cpuUtilization)) {
		if(cpuUtilization.find("cpu ") != string::npos)
			break;
	}
	boost::algorithm::split(strVec, cpuUtilization, is_any_of(" "));
	cout << strVec[2] << endl;
	dCPUUtil = (atof(strVec[2].c_str()) + atof(strVec[4].c_str())) / (atof(strVec[2].c_str()) + atof(strVec[4].c_str()) + atof(strVec[5].c_str()))*100;
	return SUCCESS;
}

int   	CHWMonitor::SetNetwork()
{
	return SUCCESS;
}

int   	CHWMonitor::SetThrottlingValue()
{
	string xml_string;
	string throttleFileLoc = m_pConfig->throttle_file;
	ifstream _throt(throttleFileLoc);
	getline(_throt, xml_string);
	dThrotling = atof(xml_string.c_str());
	return SUCCESS;
}

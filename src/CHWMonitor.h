/*
 * CHWMonitor.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CHWMONITOR_H_
#define CHWMONITOR_H_
#include "Common.h"
#include <thread>
//thread safe: worker tread and comm thread
class CHWMonitor {
public:
    CHWMonitor();
    virtual ~CHWMonitor();
    // either start thread or callback timer
    int Initialize(configInfo *info);
    void StartMonitoring();
    double GetCPUUtil();
    double GetNetwork();
    float  GetThrottlingValue();
    int   SetCPUUtil();
    int   SetNetwork();
    int   SetThrottlingValue();
    void StopThread();

private:
    double dCPUUtil;
    double dNetwork;
    float  dThrotling;
    configInfo *m_pConfig;
    std::thread *m_thread;
    bool stopThread;
    // add relevent stuff here
};

#endif /* CHWMONITOR_H_ */

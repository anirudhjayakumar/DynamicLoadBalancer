/*
 * Common.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef COMMON_H_
#define COMMON_H_

#define SUCCESS 0
#define FAIL    1

#include <cstddef>
#include <map>

struct Node {
	int nodeID;
	std::string type;
	std::string ip;
	int port;
};

struct configInfo {
	long workloadSize;
	int nJobs;
	int myNodeId;
	int remoteNodeId;
	std::map<int,Node> nodeInfo; //Containing two child nodes
	std::string throttle_file;
	int stateinfo_period;
	int transfer_policy_period;
	int monitor_period;
	std::string transfer_policy_type;
	std::string transfer_policy_algo;
	void load(const std::string &filename);
//void save(const std::string &filename);
};

#endif /* COMMON_H_ */

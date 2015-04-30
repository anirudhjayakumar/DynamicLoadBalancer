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

//#define COMPRESS

#include <cstddef>
#include <map>
#include <vector>
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
	std::string print();
//void save(const std::string &filename);
};

int GetJobSize(int);

void compress_buffer(void *in_data, size_t in_data_size, std::vector<uint8_t> &out_data);
void uncompress_buffer(std::vector<uint8_t> &in_data, std::vector<uint8_t> &out_data);
#endif /* COMMON_H_ */

/*
 * ConfigAccessor.cpp
 *
 *  Created on: Apr 19, 2015
 *      Author: Neha Chaube
 */


#define ATTR_SET ".<xmlattr>"
#define XML_PATH "./config.xml"
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
#include<boost/foreach.hpp>
#include<string>
#include<set>
#include <utility>
#include<exception>
#include "Common.h"
#include<iostream>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
using boost::property_tree::ptree;
#include <sstream>
using namespace std;

string configInfo::print()
{
	stringstream ss;
	ss << "Node: " << " id:0" << " type:" << nodeInfo[0].type << " ip:" <<
	nodeInfo[0].ip << " port:" << nodeInfo[0].port << endl;
	ss << "Node: " << " id:1" << " type:" << nodeInfo[1].type << " ip:" <<
	nodeInfo[1].ip << " port:" << nodeInfo[1].port << endl;
	ss << "Workload: " << " size:" << workloadSize << " jobs:" << nJobs << endl;
	ss << "Throttle file:" << throttle_file << endl; 	
 	ss << "HWMonitor:" << " period:" << monitor_period << endl;
	ss << "StateInfoPolicy: " << " period:" << stateinfo_period  << endl;
	ss << "TransferPolicy: " << " period:" << transfer_policy_period << " type:" << 
	transfer_policy_type << " algo:" << transfer_policy_algo << endl;
	return ss.str();
}


void configInfo::load(const std::string &filename) {
	ptree pt;
	//loads the xml file in to the property tree.If reading fails
	//(cannot open file,parse error),an exception is thrown.
	read_xml(filename, pt);
	BOOST_FOREACH(const ptree::value_type &v,pt.get_child("DynLB.Nodes")) {
		Node n;
		n.nodeID = lexical_cast<int>(v.second.get_child("<xmlattr>.id").data());
		n.type = v.second.get_child("<xmlattr>.type").data();
		n.ip = v.second.get_child("<xmlattr>.ip").data();
		n.port = lexical_cast<int>(v.second.get_child("<xmlattr>.port").data());
		nodeInfo.insert(make_pair(n.nodeID,n));
	}

	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("DynLB")) {
		if (v.first == "ThrottleInterface") {
			throttle_file = v.second.get_child("<xmlattr>.file").data();
		} else if (v.first == "StateInfoPolicy") {
			stateinfo_period = lexical_cast<int>(
					v.second.get_child("<xmlattr>.period").data());
		} else if (v.first == "TransferPolicy") {
			transfer_policy_period = lexical_cast<int>(
					v.second.get_child("<xmlattr>.period").data());
			transfer_policy_type = v.second.get_child("<xmlattr>.type").data();
			transfer_policy_algo = v.second.get_child("<xmlattr>.algo").data();
			string sCompress = v.second.get_child("<xmlattr>.compress").data();
                        if (sCompress == "true") compress = true;
                        else compress = false;
		}
		else if (v.first == "HWMonitor") {
			monitor_period = lexical_cast<int>(
					v.second.get_child("<xmlattr>.period").data());
		}
		else if (v.first == "Workload") {
			workloadSize = lexical_cast<int>(
					v.second.get_child("<xmlattr>.size").data());
			nJobs = lexical_cast<int>(
					v.second.get_child("<xmlattr>.jobs").data());
		}
	}
}

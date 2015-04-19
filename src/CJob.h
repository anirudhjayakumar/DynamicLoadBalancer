/*
 * CJob.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CJOB_H_
#define CJOB_H_

#include <vector>

class CJob {
public:
	CJob();
	virtual ~CJob();
	int DeSerialize(const char *jobptr);
	int Serialize(char **jobptr, int &bufSize);
private:
	int nJobID;
	int size; //size of the array
	double *buf; //array buffer
};

typedef std::vector<CJob*> JobVec;

#endif /* CJOB_H_ */

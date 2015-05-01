/*
 * CJob.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#ifndef CJOB_H_
#define CJOB_H_

#include <deque>
#include <vector>

class CJob {
public:
    CJob();
    CJob(int JobID,int size,double *buf);
    virtual ~CJob();
    void  ExecJob();
    int GetID();
    int DeSerialize(const char *jobptr);
    int Serialize(char **jobptr, int &bufSize);
    bool CheckIntegrity();
private:
    int nJobID;
    int size; //size of the array
    double *buf; //array buffer

};

typedef std::deque<CJob*> JobQ;
typedef std::vector<CJob*> JobVec;
#endif /* CJOB_H_ */

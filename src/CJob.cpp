/*
 * CJob.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CJob.h"
#include "Common.h"
#include <cstring>


CJob::CJob(int JobID,int size_,double *buf_) {
	nJobID = JobID;
	size = size_;
	buf = buf_;
}

CJob::~CJob() {
	// TODO Auto-generated destructor stub
	delete[] buf;
}

CJob::CJob() {

}

int CJob::GetID()
{
	return nJobID;
}

void  CJob::ExecJob()
{
	for (int count = 0; count < size; ++count)
	{
		for( int j=0; j < 1000; j++)
		{
			buf[count] += 1.111111;
		}
	}
	return;
}


int CJob::DeSerialize(const char *jobptr)
{
	nJobID = *((int *)jobptr);
	size   = *((int *)(jobptr + sizeof(int)));
	buf = new double[size];
	memcpy(buf,(void *)(jobptr + 2*sizeof(int)),size*sizeof(double));
	return SUCCESS;
}

int CJob::Serialize(char **jobptr, int &bufSize)
{
	bufSize = 2*sizeof(int) + size*sizeof(double);
	char *pBuf = new char[bufSize];
    *((int *)pBuf) = nJobID;
    *((int *)(pBuf + sizeof(int))) = size;
    memcpy((void *)(pBuf + 2*sizeof(int)), buf,size*sizeof(double));
    *jobptr = pBuf;
	return SUCCESS;
}


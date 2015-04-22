/*
 * CJob.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CJob.h"
#include "Common.h"
#include <cstring>
CJob::CJob() {
	// TODO Auto-generated constructor stub

}

CJob::~CJob() {
	// TODO Auto-generated destructor stub
	delete[] buf;
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
	memcpy(buf,(void *)(jobptr + 2*sizeof(int)),size*sizeof(double));
	return SUCCESS;
}

int CJob::Serialize(char **jobptr, int &bufSize)
{
	bufSize = 2*sizeof(int) + size*sizeof(double);
	char *pBuf = new char(bufSize);
    *((int *)pBuf) = nJobID;
    *((int *)(pBuf + sizeof(int))) = size;
    memcpy((void *)(pBuf + 2*sizeof(int)), buf,size*sizeof(double));
    *jobptr = pBuf;
	return SUCCESS;
}

int nJobID;
	int size; //size of the array
	double *buf; //array

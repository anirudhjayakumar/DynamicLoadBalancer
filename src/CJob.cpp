/*
 * CJob.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: Anirudh Jayakumar
 */

#include "CJob.h"
#include "Common.h"
#include <cstring>
#include <cmath>
#include <zlib.h>
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std;

CJob::CJob(int JobID,int size_,double *buf_) {
	nJobID = JobID;
	size = size_;
	buf = buf_;
}

CJob::~CJob() {
	// TODO Auto-generated destructor stub
	delete[] buf;
}

bool CJob::CheckIntegrity()
{
	double expectedResult = 1.111111*1000;
	for (int count = 0; count < size; ++count)
        {
		if (!(fabs(buf[count] - expectedResult) < 0.00001))
			return false;
	}
	return true;
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
/*

 * Following is the algorithm for the following compression routine
1. fill next_in with the next chunk of data you want to compress
2. set avail_in to the number of bytes available in next_in
3. set next_out to where the compressed data should be written which should usually be a pointer inside your buffer that advances as you go along
4. set avail_out to the number of bytes available in next_out
5. call deflate
6. repeat steps 3-5 until avail_out is non-zero (i.e. there's more room in the output buffer than zlib needs - no more data to write)
7. repeat steps 1-6 while you have data to compress
8. Eventually you call deflateEnd() and you're done.

You're basically feeding it chunks of input and output until you're out of input and it is out of output.

*/

void compress_buffer(void *in_data, size_t in_data_size, vector<uint8_t> &out_data) {


    vector<uint8_t> buffer;
    /* This is a random buffer size I have put as a placeholdetr and needs to be changed based on
     * our requireemnt
     */
    const size_t BUFFSIZE = 128*1024;
    uint8_t temp_buffer[BUFFSIZE];
    /*coming from zlib.h*/
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    /*receiving the incoming data in the stream*/
    strm.next_in = reinterpret_cast<uint8_t *>(in_data);
    /*informing the compressor the data size of the incoming data*/
    strm.avail_in = in_data_size;
    /*pointitng to the buffer where the output compressed data will be stored*/
    strm.next_out = temp_buffer;
    /*allocating the max size of the output buffer*/
    strm.avail_out = BUFFSIZE;

    /*Compression API from ZLIB with the BEST_COMPRESSION macro*/
    int deflate_res_init = deflateInit(&strm, Z_BEST_COMPRESSION);
    assert(deflate_res_init == Z_OK);
    while(strm.avail_in != 0) {
        int res = deflate(&strm, Z_NO_FLUSH);
        assert(res == Z_OK);
        if(strm.avail_out == 0) {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFFSIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFFSIZE;
        }
    }

    int deflate_res = Z_OK;
    while (deflate_res == Z_OK) {
        if(strm.avail_out == 0) {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFFSIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFFSIZE;
        }
        deflate_res = deflate(&strm, Z_FINISH);
    }
    assert(deflate_res == Z_STREAM_END);
    buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFFSIZE - strm.avail_out);
    int deflate_res_end = deflateEnd(&strm);
    assert(deflate_res_end == Z_OK);
    out_data.swap(buffer);
}

/*
 * This routine is just exact reverse of the deflate routine.
 * It receives a compressed data in vector and outputs all the inflated data in a vector
 */
void uncompress_buffer(vector<uint8_t> &in_data, vector<uint8_t> &out_data) {
    /*This is a random buffer size as a placeholder and needds to be changed based on our requirement*/
    const size_t BUFSIZE = 128*1024;
    uint8_t temp_buffer[BUFSIZE];
    out_data.clear();
    /*Assigning state of the decompression stream*/
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;

    int inflate_res_init  = inflateInit(&strm);
    assert(inflate_res_init == Z_OK);
    strm.avail_in = in_data.size();
    strm.next_in = &in_data[0];

    for(;;) {
        strm.next_out = &temp_buffer[0];
        strm.avail_out = BUFSIZE;
        int inflate_res = inflate(&strm, Z_NO_FLUSH);
        if(inflate_res == Z_STREAM_END) {
            for(int i = 0; i < int(BUFSIZE - strm.avail_out); i++)
                out_data.push_back(temp_buffer[i]);
            if(strm.avail_in == 0)
                break;
        }
        for(int i = 0; i < int(BUFSIZE - strm.avail_out); i++)
            out_data.push_back(temp_buffer[i]);
    }

    int inflate_res_end = inflateEnd(&strm);
    assert(inflate_res_end == Z_OK);
    cout << "###########################################" << endl;
    cout << "Size of Compressed Received Data: " << in_data.size() << endl;
    cout << "Size of Un-Compressed Received Data: " << out_data.size() << endl;
    cout << "De-Compressedion Ratio: " << out_data.size() / in_data.size() << endl;
    cout << "###########################################" << endl;
    cout << endl;
}



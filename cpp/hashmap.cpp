/*
 * =====================================================================================
 *
 *       Filename:  hashmap.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/26/2015 08:49:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

#define N 10000

// O(logN)
//typedef map<int, int> IntMap;
// O(1)
typedef unordered_map<int, int> IntMap;

int getPidMem(pid_t pid, string &mem_size)
{
	char filename[1024];

	snprintf(filename, sizeof(filename), "/proc/%d/status", pid);

	ifstream fin;
	fin.open(filename, ios::in);
	if (!fin.is_open()) {
		cout << "Open " << filename << " error" << endl;
		return -1;
	}

	char buf[1024];
	char size[100];
	char unit[100];

	while (fin.getline(buf, sizeof(buf) - 1)) {
		if (strncmp(buf, "VmRSS:", 6) != 0)
			continue;

		sscanf(buf+6, "%s%s", size, unit);
		mem_size = string(size) + string(unit);
	}

	fin.close();
	
	return 0;
}


int main(int argc, char **argv)
{
	struct timeval begin;
	struct timeval end;
	IntMap my_map;

	gettimeofday(&begin, NULL);

	for (int i = 0; i < N; ++i) {
		my_map.insert(make_pair(i, i));
	}

	gettimeofday(&end, NULL);
	double msec = (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec;
	cout << "insert N=" << N << ", cost=" << msec << endl;

	for (int i = 0; i < N; ++i) {
		my_map.find(i);
	}

	gettimeofday(&end, NULL);
	msec = (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec;
	cout << "insert and get all N=" << N << ", cost=" << msec << endl;

	string mem_size;
	getPidMem(getpid(), mem_size);
	cout << mem_size << endl;

	return 0;
}

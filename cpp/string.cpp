/*
 * ============================================================================
 *
 *       Filename:  string.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  09/06/2015 09:29:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME ()
 *   Organization:
 *
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <chrono>

using namespace std;

#ifdef _MSC_VER
#define DONT_INLINE __declspec(noinline)
#else
#define DONT_INLINE __attribute__((__noinline__))
#endif

string s0;
string s1;
string s2;
string s3;

size_t totalLength = 0;

template<char OP>
void transfer(string &&from, string &to)
{
	if (OP == 'm') {
		to = move(from);
	} else if (OP == 'c') {
		to = from;
	} else if (OP == 'd') {
		to.assign(from, 0, from.length());
	} else {
		from.swap(to);
	}
}

template<char OP>
DONT_INLINE
void func3(string &&s)
{
	transfer<OP>(move(s), s3);
	s3[0] = '3';
	totalLength += s3.length();
}

template<char OP>
DONT_INLINE
void func2(string &&s)
{
	transfer<OP>(move(s), s2);
	s2[0] = '2';
	func3<OP>(move(s2));
}

template<char OP>
DONT_INLINE
void func1(string &&s)
{
	transfer<OP>(move(s), s1);
	s1[0] = '1';
	func2<OP>(move(s1));
}

template<char OP>
void generate(size_t minSize, size_t iterations)
{
	for (size_t count = 0; count < iterations; ++count) {
		s0.assign(minSize + count % 15, char('A' + count % 26));
		func1<OP>(move(s0));
	}
}

#if 0
m 1 50000000
c 1 50000000
d 1 50000000
s 1 50000000
m 25 50000000
c 25 50000000
d 25 50000000
s 25 50000000
#endif

int main(int argc, char *argv[])
{
#if 0
	string str1 = "hello world"; // string str1("hello world");
	string str2 = str1; // calling copy ctor

	cout << "str1 addr: " << static_cast<void *>(&str1) << ' ' << str1.c_str() << endl;
	cout << "str2 addr: " << static_cast<void *>(&str2) << ' ' << str2.c_str() << endl;
	printf("str1: %p\n", str1.c_str());
	printf("str2: %p\n", str2.c_str());

	str1[1] = 'q';
	str2[1] = 'w';

	cout << "after copy-on-write:" << endl;
	cout << "str1 addr: " << static_cast<void *>(&str1) << ' ' << str1.c_str() << endl;
	cout << "str2 addr: " << static_cast<void *>(&str2) << ' ' << str2.c_str() << endl;
	printf("str1: %p\n", str1.c_str());
	printf("str2: %p\n", str2.c_str());
#endif

	if (argc != 4) {
		cerr << "Usage: " << argv[0]
			<< " <m|c|d|s> <min size> <iterations>" << endl
			<< "Where: m = move" << endl
			<< "       c = copy" << endl
			<< "       d = copy-defeating-copy-on-write" << endl
			<< "       s = swap" << endl;

		return EXIT_FAILURE;
	}

	size_t minSize = static_cast<size_t>(atoi(argv[2]));
	size_t iterations = static_cast<size_t>(atoi(argv[3]));

	chrono::steady_clock::time_point startTime = chrono::steady_clock::now();

	if (argv[1][0] = 'm') {
		generate<'m'>(minSize, iterations);
	} else if (argv[1][0] = 'c') {
		generate<'c'>(minSize, iterations);
	} else if (argv[1][0] = 'd') {
		generate<'d'>(minSize, iterations);
	} else {
		generate<'s'>(minSize, iterations);
	}

	chrono::steady_clock::time_point endTime = chrono::steady_clock::now();

	size_t durationMs = chrono::duration_cast<chrono::milliseconds>(endTime -
			 startTime).count();

	cout << "Time: " << durationMs << "ms" << endl;
	cout << "Total length: " << totalLength << endl;

	cout << s0 << endl;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;

	return EXIT_SUCCESS;
}

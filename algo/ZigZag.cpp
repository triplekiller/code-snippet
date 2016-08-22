//https://community.topcoder.com/stat?c=problem_statement&pm=1259
//https://rafal.io/posts/topcoder-zigzag.html

#include <iostream>
#include <vector>

using namespace std;

class ZigZag {
public:
	inline int sign(int a, int b) {
		if (a > b)
			return 1;
		else if (a < b)
			return -1;
		else
			return 0;
	}

	int longestZigZag(vector<int> sequence);
};

int ZigZag::longestZigZag(vector<int> sequence)
{
	size_t len = sequence.size();
	// longestLen(i) ==> longest zig-zag sequence len including the ith element
	vector<int> longestLen(len, 1);
	// the last sign(+ or - or zero) for longestLen(i)
	vector<int> lastSign(len, 0);

	for (int i = 1; i < len; i++) {
		int maxLen = longestLen[i];
		int index = 0;
		for (int j = i - 1; j >= 0; j--) {
			// find the max length for (i-1, 0)
			int sign_ij = sign(sequence[i], sequence[j]);
			if (sign_ij != 0 && sign_ij != lastSign[j]) {
				if (longestLen[j] + 1 > maxLen) {
					maxLen = longestLen[j] + 1;
					index = j;
				}
			}
		}

		longestLen[i] = maxLen;
		lastSign[i] = sign(sequence[i], sequence[index]);
	}

	return longestLen[len - 1];
}

int main(int argc, char *argv[])
{
//	vector<int> seq = {44};
//	vector<int> seq = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//	vector<int> seq = {1, 7, 4, 9, 2, 5};
//	vector<int> seq = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
//	vector<int> seq = {70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32};
	vector<int> seq = {374, 40, 854, 203, 203, 156, 362, 279, 812, 955,
		600, 947, 978, 46, 100, 953, 670, 862, 568, 188,
		67, 669, 810, 704, 52, 861, 49, 640, 370, 908,
		477, 245, 413, 109, 659, 401, 483, 308, 609, 120,
		249, 22, 176, 279, 23, 22, 617, 462, 459, 244};

	ZigZag test;

	cout << test.longestZigZag(seq) << endl;

	return 0;
}

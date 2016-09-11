// https://community.topcoder.com/stat?c=problem_statement&pm=13918

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cassert>

using namespace std;

class ABBA {
public:
	string canObtain(string initial, string target);
};

string ABBA::canObtain(string initial, string target)
{
	size_t initial_len = initial.length();

	while (target.length() > initial_len) {
		if (target.back() == 'A') {
			target.pop_back();
		} else if (target.back() == 'B') {
			target.pop_back();
			reverse(target.begin(), target.end());
		}
	}

	return target == initial ? "Possible" : "Impossible";
}

void TEST(string initial, string target, string expected)
{
	clock_t begin, end;
	double ticks_used;
	ABBA test;

	begin = clock();
	string result = test.canObtain(initial, target);
	assert(result == expected);
	end = clock();

	ticks_used = double(end - begin);
	cout << "Time taken: " << ticks_used << " clock ticks, " << \
		ticks_used / CLOCKS_PER_SEC << " seconds" << endl;

	return;
}

int main(int argc, char *argv[])
{
#if 0
	if (argc != 3) {
		cout << "Usage:" << endl;
		cout << "    " << argv[0] << " <initial_string> <target_string>" << endl;
		return -1;
	}

	string initial = argv[1];
	string target = argv[2];
	ABBA test;

	cout << test.canObtain(initial, target) << endl;
#endif

	cout << "CLOCKS_PER_SEC=" << CLOCKS_PER_SEC << endl;

	TEST("B", "ABBA", "Possible");
	TEST("AB", "ABB", "Impossible");
	TEST("BBAB", "ABABABABB", "Impossible");
	TEST("BBBBABABBBBBBA", "BBBBABABBABBBBBBABABBBBBBBBABAABBBAA", "Possible");

	cout << "Test done" << endl;

	return 0;
}

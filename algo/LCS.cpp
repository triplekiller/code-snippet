//http://www.algorithmist.com/index.php/Longest_Common_Subsequence

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef vector<int>::iterator vector_iter;

class LCS {
public:
	int recursiveFindLCS(vector<int> a, vector<int> b);
	int findLCS(vector<int> a, vector<int> b);
};

int LCS::recursiveFindLCS(vector<int> a, vector<int> b)
{
	int n = a.size();
	int m = b.size();
	if (n == 0 || m == 0) {
		return 0;
	}

	if (a[n - 1] == b[m - 1]) {
		return recursiveFindLCS(vector<int>(a.begin(), a.begin() + n - 1),
			vector<int>(b.begin(), b.begin() + m - 1)) + 1;
	} else {
		return max(recursiveFindLCS(vector<int>(a.begin(), a.begin() + n - 1), b),
			recursiveFindLCS(a, vector<int>(b.begin(), b.begin() + m - 1)));
	}
}

int LCS::findLCS(vector<int> a, vector<int> b)
{
	int n = a.size();
	int m = b.size();
	if (n == 0 || m == 0)
		return 0;

	int N = max(n, m);
	vector<int> cs(N);
	cs[0] = (a[0] == b[0] ? 1 : 0);
	vector_iter iter_a, iter_b;

	for (int i = 1; i < N; i++) {
		cs[i] = cs[i - 1];
		if (i < min(n, m)) {
			iter_a = find(a.begin(), a.begin() + i + 1, b[i]);
			if (iter_a != a.begin() + i + 1)
				cs[i] = max(cs[i], cs[iter_a - a.begin()] + 1);

			iter_b = find(b.begin(), b.begin() + i + 1, a[i]);
			if (iter_b != b.begin() + i + 1 && iter_b - b.begin() != iter_a - a.begin())
				cs[i] = max(cs[i], cs[iter_b - b.begin()] + 1);
		} else {
			if (N == n) {
				iter_b = find(b.begin(), b.end(), a[i]);
				if (iter_b != b.end())
					cs[i] = max(cs[i], cs[iter_b - b.begin()] + 1);
			} else {
				iter_a = find(a.begin(), a.end(), b[i]);
				if (iter_a != a.end())
					cs[i] = max(cs[i], cs[iter_a - a.begin()] + 1);
			}
		}
	}

	return cs[N - 1];
}

int main(int argc, char **argv)
{
	vector<int> a = {9, 6, 5, 7, 8, 9, 5, 4, 7};
	vector<int> b = {9, 6, 9, 8, 3, 4};

	LCS test;

	cout << test.findLCS(a, b) << endl;
	cout << test.recursiveFindLCS(a, b) << endl;

	return 0;
}

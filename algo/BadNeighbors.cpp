// https://community.topcoder.com/stat?c=problem_statement&pm=2402&rd=5009

// dp[i] = x0 (i=0)
// dp[i] = max(x0, x1) (i=1)
// dp[i] = max(dp[i-1], dp[i-2]+xi) (i>=2)

#include <iostream>
#include <vector>
#include <algorithm>

//#define NDEBUG
#include <cassert>

using namespace std;

class BadNeighbors {
public:
	int subMaxDonations(int low, int heigh, vector<int> &amount);
	int maxDonations(vector<int> amount);
};

int BadNeighbors::subMaxDonations(int low, int heigh, vector<int> &amount)
{
	assert(heigh >= low);
	if (heigh - low < 2) {
		return max(amount[low], amount[heigh]);
	}

	vector<int> sum(heigh - low + 1);
	sum[0] = amount[low];
	sum[1] = max(amount[low], amount[low + 1]);

	for (int i = low+2; i <= heigh; i++) {
		sum[i - low] = max(sum[i - low - 1], sum[i - low - 2] + amount[i]);
	}

	return sum[heigh - low];
}

int BadNeighbors::maxDonations(vector<int> amount)
{
	int num = amount.size();
	if (num < 3)
		return *max_element(amount.begin(), amount.end());

	return max(subMaxDonations(0, num - 2, amount),
		subMaxDonations(1, num - 1, amount));
}

int donations[] = {90, 1, 2, 89, 3, 4, 88, 5, 6, 87, 5, 4, 86, 3, 2, 85};
//int donations[] = {4, 3, 1, 2, 8, 3, 4};
//int donations[] = {10, 3, 2, 5, 7, 8};
//int donations[] = {11, 15};
//int donations[] = {7, 7, 7, 7, 7, 7, 7};
//int donations[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
/*
int donations[] = {94, 40, 49, 65, 21, 21, 106, 80, 92, 81, 679, 4, 61,
  6, 237, 12, 72, 74, 29, 95, 265, 35, 47, 1, 61, 397,
  52, 72, 37, 51, 1, 81, 45, 435, 7, 36, 57, 86, 81, 72};
*/

int main(int argc, char *argv[])
{
	BadNeighbors BN;

	int num = sizeof(donations) / sizeof(donations[0]);
	cout << BN.maxDonations(vector<int>(donations, donations+num)) << endl;

	return 0;
}

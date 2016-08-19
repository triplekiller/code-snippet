// http://www.algorithmist.com/index.php/Longest_Increasing_Subsequence
// LIS(i) = max{LIS(j)+1} (j<i and a[j]<a[i])

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LIS {
public:
	int getLIS(vector<int> array);
};

int LIS::getLIS(vector<int> array)
{
	int num = array.size();

	// build a table with lengths of LIS for each index
	// maxSeq[i]: the length of LIS ending with element numbered i
	vector<int> maxSeq(num, 1);

	for (int i = 1; i < num; i++) {
		int prevMax = maxSeq[i];
		for (int j = i - 1; j >= 0; j--) {
			if (array[i] > array[j]) {
				prevMax = max(prevMax, maxSeq[j] + 1);
			}
		}

		maxSeq[i] = prevMax;
	}

	return *max_element(maxSeq.begin(), maxSeq.end());
}

int a[] = {4, 3, 1 ,2, 8, 3, 4};
//int a[] =  {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

int main(int argc, char *argv[])
{
	int num = sizeof(a) / sizeof(a[0]);
	LIS lis;
	cout << lis.getLIS(vector<int>(a, a + num)) << endl;

	return 0;
}

// http://www.algorithmist.com/index.php/Longest_Increasing_Subsequence
// LIS(i) = max{LIS(j)+1} (0<=j<i and a[j]<a[i])

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class LIS {
public:
	int getLIS(vector<int> array, vector<int> &seq);
};

int LIS::getLIS(vector<int> array, vector<int> &seq)
{
	int num = array.size();

	// build a table with lengths of LIS for each index
	// maxSeq[i]: the length of LIS ending with element numbered i
	vector<int> maxSeq(num, 1);
	vector<int> prevIndex(num, -1);

	for (int i = 1; i < num; i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (array[i] > array[j] && maxSeq[j] + 1 > maxSeq[i]) {
				maxSeq[i] = maxSeq[j] + 1;
				prevIndex[i] = j;
			}
		}
	}

	int result, index;
	vector<int>::iterator iter = max_element(maxSeq.begin(), maxSeq.end());
	result = *iter;
	index = distance(maxSeq.begin(), iter);
	while (index >= 0) {
		seq.push_back(array[index]);
		index = prevIndex[index];
	}

	return result;
}

//int a[] = {1, 4, 6, 2, 8, 9, 7};
//int a[] = {4, 3, 1 ,2, 8, 3, 4};
int a[] =  {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

int main(int argc, char *argv[])
{
	int num = sizeof(a) / sizeof(a[0]);
	LIS lis;
	vector<int> seq;

	struct func {
		void operator() (int i) {
			cout << i << ' ';
		}
	} my_func;

	cout << lis.getLIS(vector<int>(a, a + num), seq) << endl;

	for_each(seq.rbegin(), seq.rend(), [](int i) {
		cout << i << ' '; });
//	for_each(seq.begin(), seq.end(), my_func);
	cout << endl;

	return 0;
}

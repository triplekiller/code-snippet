//https://community.topcoder.com/stat?c=problem_statement&pm=2940&rd=5854

#include <iostream>
#include <vector>

using namespace std;

// class access level default: private (CPP OO and encapsulation)
// struct access level default: public (compatible with C)
// class: default private inherit
// struct: default public inherit

class StarAdventure {
public:
	int mostStars(vector<string> &level);
};

int StarAdventure::mostStars(vector<string> &level)
{
	size_t row = level.size();
	size_t column = level[0].size();

	int sum[row][column];
	sum[0][0] = int(level[0][0] - 0x30);
	pair<int, int> prev[row][column];
	prev[0][0] = make_pair(0, 0);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (i == 0 && j == 0)
				continue;

			if (i == 0) {
				sum[i][j] = sum[i][j - 1] + int(level[i][j] - 0x30);
				prev[i][j] = make_pair(i, j - 1);
			} else if (j == 0) {
				sum[i][j] = sum[i - 1][j] + int(level[i][j] - 0x30);
				prev[i][j] = make_pair(i - 1, j);
			} else {
				sum[i][j] = max(sum[i][j - 1], sum[i - 1][j]) + int(level[i][j] - 0x30);
				if (sum[i][j - 1] > sum[i - 1][j])
					prev[i][j] = make_pair(i, j - 1);
				else
					prev[i][j] = make_pair(i - 1, j);
			}
		}
	}

	pair<int, int> index = make_pair(row - 1, column - 1);
	while (index != make_pair(0, 0)) {
		level[index.first][index.second] = '0';
		index = prev[index.first][index.second];
	}

	return sum[row - 1][column - 1];
}

int main(int argc, char *argv[])
{
#if 0
	vector<string> level = {
		"01",
		"11"
	};
#endif

#if 0
	vector<string> level = {
		"0123",
		"7654",
		"8999",
		"9123"
	};
#endif

#if 0
	vector<string> level = {
		"0999999999",
		"9999999999",
		"9999999999",
		"9999999999",
		"9999999999",
		"9999999999",
		"9999999999",
		"9999999999",
		"9999999999",
		"9999999999"
	};
#endif

#if 0
	vector<string> level = {
		"012",
		"012",
		"012",
		"012",
		"012",
		"012",
		"012"
	};
#endif

#if 1
	vector<string> level = {
		"0123456789",
		"1123456789",
		"2223456789",
		"3333456789",
		"4444456789",
		"5555556789",
		"6666666789",
		"7777777789",
		"8888888889",
		"9999999999"
	};
#endif

	StarAdventure test;
	vector<string> trim_level = level;

	int maxStars = test.mostStars(trim_level) + test.mostStars(trim_level) +
		test.mostStars(trim_level);

	cout << "Most stars: " << maxStars << endl;

	return 0;
}

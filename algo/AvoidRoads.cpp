//https://community.topcoder.com/stat?c=problem_statement&pm=1889

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class AvoidRoads {
public:
	long numWays(int width, int height, vector<string> bad);
	long numWaysDP(int width, int height, vector<string> bad);
};

// plain recursive
long AvoidRoads::numWays(int width, int height, vector<string> bad)
{
	if (width == 0 && height == 0)
		return 1;

	bool x_block = false;
	bool y_block = false;

	string horizontal, vertical;
	string horizontal2, vertical2;

	if (width == 0)
		x_block = true;
	else {
		horizontal = {static_cast<char>(width - 1 + 0x30), ' ', static_cast<char>(height + 0x30),
			' ', static_cast<char>(width + 0x30), ' ', static_cast<char>(height + 0x30)};

		horizontal2 = {static_cast<char>(width + 0x30), ' ', static_cast<char>(height + 0x30),
			' ', static_cast<char>(width - 1 + 0x30), ' ', static_cast<char>(height + 0x30)};

		if (find(bad.begin(), bad.end(), horizontal) != bad.end() ||
			find(bad.begin(), bad.end(), horizontal2) != bad.end())
			x_block = true;
	}

	if (height == 0)
		y_block = true;
	else {
		vertical = {static_cast<char>(width + 0x30), ' ', static_cast<char>(height - 1 + 0x30),
			' ', static_cast<char>(width + 0x30), ' ', static_cast<char>(height + 0x30)};

		vertical2 = {static_cast<char>(width + 0x30), ' ', static_cast<char>(height + 0x30),
			' ', static_cast<char>(width + 0x30), ' ', static_cast<char>(height - 1 + 0x30)};

		if (find(bad.begin(), bad.end(), vertical) != bad.end() ||
			find(bad.begin(), bad.end(), vertical2) != bad.end())
			y_block = true;
	}

	if (x_block && y_block)
		return 0;
	else if (x_block)
		return numWays(width, height - 1, bad);
	else if (y_block)
		return numWays(width - 1, height, bad);
	else
		return numWays(width, height - 1, bad) + numWays(width - 1, height, bad);
}

// DP
long AvoidRoads::numWaysDP(int width, int height, vector<string> bad)
{
	long path[width + 1][height + 1];

	int i, j;
	string horizontal, horizontal2, vertical, vertical2;
	bool x_block = false;
	bool y_block = false;

	for (i = 0; i <= width; i++) {
		for (j = 0; j <= height; j++) {
			x_block = y_block = false;
			if (i == 0 && j == 0) {
				path[i][j] = 1;
				continue;
			}

			if (i == 0)
				x_block = true;
			else {
				horizontal = {static_cast<char>(i - 1 + 0x30), ' ', static_cast<char>(j + 0x30),
					' ', static_cast<char>(i + 0x30), ' ', static_cast<char>(j + 0x30)};
				horizontal2 = {static_cast<char>(i + 0x30), ' ', static_cast<char>(j + 0x30),
					' ', static_cast<char>(i - 1 + 0x30), ' ', static_cast<char>(j + 0x30)};

				if (find(bad.begin(), bad.end(), horizontal) != bad.end() ||
					find(bad.begin(), bad.end(), horizontal2) != bad.end())
					x_block = true;
			}

			if (j == 0)
				y_block = true;
			else {
				vertical = {static_cast<char>(i + 0x30), ' ', static_cast<char>(j - 1 + 0x30),
					' ', static_cast<char>(i + 0x30), ' ', static_cast<char>(j + 0x30)};
				vertical2 = {static_cast<char>(i + 0x30), ' ', static_cast<char>(j + 0x30),
					' ', static_cast<char>(i + 0x30), ' ', static_cast<char>(j - 1 + 0x30)};

				if (find(bad.begin(), bad.end(), vertical) != bad.end() ||
					find(bad.begin(), bad.end(), vertical2) != bad.end())
					y_block = true;
			}

			if (x_block && y_block)
				path[i][j] = 0;
			else if (x_block)
				path[i][j] = path[i][j - 1];
			else if (y_block)
				path[i][j] = path[i - 1][j];
			else
				path[i][j] = path[i][j - 1] + path[i - 1][j];
		}
	}

	return path[width][height];
}

int main(int argc, char *argv[])
{
//	int width = 35;
//	int height = 31;
//	vector<string> bad;

//	int width = 1;
//	int height = 1;
//	vector<string> bad;

	int width = 6;
	int height = 6;
	vector<string> bad = {"0 0 0 1", "6 6 5 6"};

//	int width = 2;
//	int height = 2;
//	vector<string> bad = {"0 0 1 0", "1 2 2 2", "1 1 2 1"};

	AvoidRoads test;

//	too slow to run for the recursive method
	cout << "Recursion>> " << test.numWays(width, height, bad) << endl;
	cout << "DP>> " << test.numWaysDP(width, height, bad) << endl;

	return 0;
}

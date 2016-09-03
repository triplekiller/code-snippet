//http://www.cnblogs.com/little-YTMM/p/5372680.html

#include <iostream>
#include <vector>

class MakeChanges {
public:
	long getChanges(std::vector<int> changes, long total);
};

long MakeChanges::getChanges(std::vector<int> changes, long total)
{
	size_t len = changes.size();
	// dp[i][j] denotes the number of combinations that j dollars can be
	// changed by the changes less or equal than i dollar
	long dp[len][total + 1];

	for (int j = 0; j <= total; j++) {
		dp[0][j] = 1;
	}

	for (int i = 1; i < len; i++) {
		dp[i][0] = 1;
		for (int j = 1; j <=total; j++) {
			if (j >= changes[i]) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - changes[i]];
			} else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	return dp[len - 1][total];
}

int main(int argc, char *argv[])
{
	std::vector<int> changes = {1, 2, 5, 10, 20, 50, 100};
	long money = 1000;

	MakeChanges test;
	long ways = test.getChanges(changes, money);

	std::cout << "Money "  << money << " changed in " << ways << " ways" \
		<< std::endl;

	return 0;
}

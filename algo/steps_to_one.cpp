// http://edusagar.com/questions/dynamic-programming/dynamic-programming-minimum-steps-to-1
// f(n) = min{f(n-1), f(n/2), f(n/3)} + 1 (n > 1)

// overlapping subproblems
// optimal substructure

// Top-Down: Start solving the given problem by breaking it down. If you see
// that the problem has been solved already, then just return the saved answer.
// If it has not been solved, solve it and save the answer. This is usually
// easy to think of and very intuitive. This is referred to as Memoization.

// Bottom-Up: Analyze the problem and see the order in which the sub-problems
// are solved and start solving from the trivial subproblem, up towards the
// given problem. In this process, it is guaranteed that the subproblems are
// solved before solving the problem. This is referred to as Dynamic Programming.

// You need to traverse over your dataset and try each and every possible subproblem.
// Use extra space to save intermediate results for subproblems.
// Reuse the already saved results instead of recomputing.

#include <iostream>
#include <vector>

using namespace std;

class StepsToOne {
public:
	int getMinSteps(int n);
	int getMinStepsMemo(int n, vector<int> memo);
	int getMinStepsDP(int n);
};

// plain recursive
// a lot of recursive function calls for the same subproblem again and again
int StepsToOne::getMinSteps(int n)
{
	if (n <= 1)
		return 0;

	int minSteps = getMinSteps(n - 1) + 1;

	if (n % 2 == 0)
		minSteps = min(minSteps, getMinSteps(n / 2) + 1);
	if (n % 3 == 0)
		minSteps = min(minSteps, getMinSteps(n / 3) + 1);

	return minSteps;
}

// top down DP
int StepsToOne::getMinStepsMemo(int n, vector<int> memo)
{
	if (n == 0)
		return 0;

	// Solved it already
	if (memo[n] != -1)
		return memo[n];

	// '-1' step
	int minSteps = getMinSteps(n - 1) + 1;

	// '/2' step
	if (n % 2 == 0)
		minSteps = min(minSteps, getMinSteps(n / 2) + 1);
	// '/3' step
	if (n % 3 == 0)
		minSteps = min(minSteps, getMinSteps(n / 3) + 1);

	// If forget this step, then the same as plain recursion
	memo[n] = minSteps;

	return minSteps;
}

// bottom up DP
int StepsToOne::getMinStepsDP(int n)
{
	int dp[n + 1];
	dp[1] = 0;

	for (int i = 2; i <=n; i++) {
		dp[i] = dp[i - 1] + 1;

		if (i % 2 == 0)
			dp[i] = min(dp[i], dp[i / 2] + 1);
		if (i % 3 == 0)
			dp[i] = min(dp[i], dp[i / 3] + 1);
	}

	return dp[n];
}

int main(int argc, char *argv[])
{
	int n = 10;
	StepsToOne obj;

	cout << "Plain Recursion: " << obj.getMinSteps(n) << endl;

	vector<int> memo(n + 1, -1);
	cout << "Top Down Memoization: " << obj.getMinStepsMemo(n, memo) << endl;

	cout << "Bottom Up DP: " << obj.getMinStepsDP(n) << endl;

	return 0;
}

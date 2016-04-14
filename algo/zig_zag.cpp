#include <iostream>
#include <string>

using namespace std;

void printZigZag(string str, int n)
{
	if (n == 1) {
		cout << str;
		return;
	}

	string arr[n];
	bool down;
	int row = 0;
	int len = str.length();

	for (int i = 0; i < len; ++i) {
		arr[row].push_back(str[i]);

		if (row == n - 1)
			down = false;
		else if (row == 0)
			down = true;

		(down) ? (row++) : (row--);
	}

	for (int i = 0; i < n; ++i)
		cout << arr[i];
}

/*
 "GEEKSFORGEEKS"

 G   S   G   S
  E K F R E K
   E   O   E
*/

int main()
{
//	string str = "GEEKSFORGEEKS";
	string str = "PAHNAPLSIIGYIR";
	int n = 3;
	printZigZag(str, n);
	cout << std::endl;

	return 0;
}

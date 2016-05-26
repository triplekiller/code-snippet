/*
 * =====================================================================================
 *
 *       Filename:  priority_queue.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/28/2015 08:00:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
	int x, y;
	Node(int a = 0, int b = 0) : x(a), y(b) {}
};

struct cmp {
	bool operator() (Node a, Node b) {
		if (a.x == b.x)
			return a.y > b.y;
		return a.x > b.x;
	}
};


int main()
{
	priority_queue<Node, vector<Node>, cmp> q;

	for (int i = 0; i < 10; ++i)
		q.push(Node(rand(), rand()));

	while (!q.empty()) {
		cout << q.top().x << " " << q.top().y << endl;
		q.pop();
	}

	return 0;
}

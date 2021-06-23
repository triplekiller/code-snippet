// Heap data structure is always a Complete Binary Tree, which means all levels of
// the tree are fully filled. In Min Heap, both the children of each of the nodes
// are greater than their parents.

// top/empty/size/push/emplace/pop/swap

// ascending queue
// priority_queue <int, vector<int>, greater<int> > q;
// decending queue
// priority_queue <int, vector<int>, less<int> > q;

// greater和less是std实现的两个仿函数（就是使一个类的使用看上去像一个函数。其实
// 现就是类中实现一个operator()，这个类就有了类似函数的行为，就是一个仿函数类了

// template<typename T, typename Container=std::vector<T>, typename Compare=std::less<T>>
// class priority_queue {};

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

// Function to print the elements of the Min heap
void show(priority_queue<int, vector<int>, greater<int> > q) {
	priority_queue<int, vector<int>, greater<int> > mh = q;

	while (!mh.empty()) {
		cout << "\t" << mh.top();
		mh.pop();
	}

	cout << endl;
}

int main()
{
	priority_queue<Node, vector<Node>, cmp> q;

	for (int i = 0; i < 10; ++i)
		q.push(Node(rand(), rand()));

	while (!q.empty()) {
		cout << q.top().x << " " << q.top().y << endl;
		q.pop();
	}

	/* Declaring a Priority Queue of integers
	 * Note: by default the priority queue is Max heap in c++ :
	 * priority_queue<int> q
	 * To create a Min heap, follow the below declaration of the
	 * Priority Queue
	 **/

	priority_queue<int, vector<int>, greater<int> > minHeap;

	for (int i = 1; i < 6; i++) {
		minHeap.push(i * 20);
    }

	cout << "\n\nThe elements of the Min Heap are: ";
	show(minHeap);

	cout << "\n\nAfter Deleting the first or the smallest element from the Min Heap, it becomes: ";
	minHeap.pop();
	show(minHeap);

	cout << "\n\n\n";

	return 0;
}

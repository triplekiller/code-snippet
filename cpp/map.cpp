/*
 * =====================================================================================
 *
 *       Filename:  map.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/22/2015 10:08:36 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

class Student {
public:
	Student() {}

	Student(int id, int age) {
		m_id = id;
		m_age = age;
	}

	Student(const Student &so) {
		m_id = so.m_id;
		m_age = so.m_age;
	}

	int m_id;
	int m_age;
};

int main()
{
	map<string, Student> ms;
	ms["Alice"] = Student(111, 22);
	ms["Bruce"] = Student(222, 20);
	ms["Mike"] = Student(333, 24);
	ms["Ethan"] = Student(444, 23);
	ms.at("Ethan") = Student(555, 26);

	for (auto &x: ms)
		cout << x.first << ": " << x.second.m_id << " " << x.second.m_age << endl;

	// cbegin means const begin iterator
	for (auto i = ms.cbegin(); i != ms.cend(); ++i)
		cout << i->first << ": " << i->second.m_id << " " << i->second.m_age << endl;

	// unordered_map by hash while map by AVL or RB tree
	// O(1) search/insert/delete vs O(logN) search/insert/delete
	unordered_map<int, string> dict = {{1, "one"}, {2, "two"}};
	dict.insert({3, "three"});
	dict.insert(make_pair(4, "four"));
	dict.insert({{4, "another four"}, {5, "five"}});

	bool ok=dict.insert({1, "another one"}).second;
	cout << "insert " << (ok ? "success" : "fail") << endl;
	for (auto &p : dict)
		cout << " " << p.first << " => " << p.second << endl;

	return 0;
}

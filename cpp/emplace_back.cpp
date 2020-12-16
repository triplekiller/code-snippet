#include <iostream>
#include <vector>
#include <string>

// g++ -std=c++11 emplace_back.cpp

using namespace std;

struct President {
  string name_;
  string country_;
  int year_;

  President(string name, string country, int year) : name_(move(name)),
    country_(move(country)), year_(year) {
    cout << "Being constructed" << endl;
  }

  President(President&& other) : name_(move(other.name_)),
    country_(move(other.country_)), year_(other.year_) {
    cout << "Being moved" << endl;
  }

  President& operator=(const President& other) = default;
};

int main() {
  vector<President> elections;
  cout << "emplace_back:\n";
//  elections.emplace_back("Nelson Mandela", "South Africa", 1994);
  elections.emplace_back("Nelson Mandela", "South Africa", 1994);

  vector<President> reElections;
  cout << "\npush_back:\n";
  reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));


   cout << "\nContents:\n";
   for (President const& president: elections) {
     cout << president.name_ << " was elected president of "
                  << president.country_ << " in " << president.year_ << ".\n";
   }

    for (President const& president: reElections) {
      std::cout << president.name_ << " was re-elected president of "
                  << president.country_ << " in " << president.year_ << ".\n";
    }

  return 0;
}

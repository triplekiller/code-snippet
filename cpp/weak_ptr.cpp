#include <iostream>
#include <memory>

// A Circular reference (also called a cyclical reference or a cycle) is a
// series of references where each object references the next, and the last
// object references back to the first, causing a referential loop. The
// references do not need to be actual C++ references -- they can be pointers,
// unique IDs, or any other means of identifying specific objects.

// In the context of shared pointers, the references will be pointers.

// std::weak_ptr was designed to solve the “cyclical ownership” problem
// described above. A std::weak_ptr is an observer -- it can observe and access
// the same object as a std::shared_ptr (or other std::weak_ptrs) but it is not
// considered an owner. Remember, when a std::shared pointer goes out of scope,
// it only considers whether other std::shared_ptr are co-owning the object.
// std::weak_ptr does not count!

class Person {
 public:
  Person(const std::string& name) : name_(name) {
    std::cout << name_ << " created\n";
  }

  ~Person() {
    std::cout << name_ << " destroyed\n";
  }

  // member function as friend to access private member variable `name_`
  friend bool PartnerUp(std::shared_ptr<Person>& p1,
                        std::shared_ptr<Person>& p2) {
    if (!p1 || !p2) {
      return false;
    }

    p1->partner_ = p2;
    p2->partner_ = p1;

    std::cout << p1->name_ << " is now partnered with " << p2->name_
              << std::endl;

    return true;
  }

 private:
  std::string name_;
  //    The practical effect of having shared pointers form a cycle is that each
  //    object ends up keeping the next object alive -- with the last object
  //    keeping the first object alive. Thus, no objects in the series can be
  //    deallocated because they all think some other object still needs it!

  //   std::shared_ptr<Person> partner_;
  std::weak_ptr<Person> partner_;
};

int main(int argc, char** argv) {
  auto lucy = std::make_shared<Person>("Lucy");
  auto ricky = std::make_shared<Person>("Ricky");

  PartnerUp(lucy, ricky);  // Make "Lucy" point to "Ricky" and vice-versa

  return 0;
}
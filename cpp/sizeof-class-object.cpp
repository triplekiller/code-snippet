#include <iostream>

// For offsetof()
#include <stddef.h>

using namespace std;

// https://www.includehelp.com/cpp-tutorial/size-of-a-class-in-cpp-padding-alignment-in-class-size-of-derived-class.aspx
// https://stackoverflow.com/questions/45697799/determine-total-size-of-static-variables-of-class

// There are many factors that decide the size of an object of a class in C++.
// 1. Size of all non-static data members
// 2. Order of data members
// 3. Byte alignment or byte padding
// 4. Size of its immediate base class
// 5. The existence of virtual function(s) (Dynamic polymorphism using virtual functions).
// 6. Compiler being used
// 7. Mode of inheritance (virtual inheritance)

class FooStatic {
 private:
  float mem1_;
  const int mem2_;
  static int mem3_; // static members are not part of the class object
  char mem4_;
};

struct FooOrder {
 public:
  char mem1_;
  int mem2_;
  int mem3_;
  int mem4_;
  long mem5_;
  short mem6_;
};

class FooOrder2 {
  int mem1_;
  int mem2_;
  int mem3_;
  long mem4_;
  short mem5_;
  char mem6_;
};

// sizeof(Base)=16 since vptr is 8 bytes in 64-bit arch
class Base {
 public:
  virtual void BaseFunc();

  int mem1_;
  int mem2_;
};

// The size of a class also include size of its immediate base class.
// Existence of virtual function(s) will add 8 bytes of virtual table pointer in
// the class for 64-bit arch.

// sizeof(Derived)=24
class Derived: public Base {
 public:
  virtual void DerivedFunc();

  int mem_;
};

class BaseClass {
  int a;
  char c;
};

// for g++, sizeof(DerivedClass)=12
// for MS C++ compiler, sizeof(DerivedClass)=16
class DerivedClass : public BaseClass {
  char d;
  int i;
};

class ABase {
  int mem_;
};

// introduce an overhead of 8 bytes of virtual base pointer in 64-bit arch
// sizeof(BBase)=16 in 64-bit arch
class BBase : public virtual ABase {
  int mem_;
};

class CBase : public virtual ABase {
  int mem_;
};

// sizeof(DBase)=40 in 64-bit arch
// maintain only one virtual base pointer
class DBase : public BBase, public CBase {
  int mem_;
};

/*
Inorder to avoid misalignment for struct/class arrays, compiler will introduce
alignment requirement to every structure. It will be as that of the largest
member of the structure. For nested structures, the size of largest inner
structure will be the alignment of immediate larger structure.

A variable’s data alignment deals with the way the data stored in memory banks.
For example, the natural alignment of int on 32-bit machine is 4 bytes. When a
data type is naturally aligned, the CPU fetches it in minimum read cycles.
*/

// nm --demangle --print-size a.out | egrep -i ' [bdgsr] '
class StaticFoo {
  static void StaticFunc();

  void MemFunc(); 

  static int mem_int_;
  static long mem_long_;
  static char array_[];
  static const char *str_;
};

void StaticFoo::MemFunc() {
  static double f = 0.5;
}

int StaticFoo::mem_int_ = 5;
char StaticFoo::array_[42];
const char *StaticFoo::str_ = "hello, world?";

int main() {
  cout << "sizeof(int): " << sizeof(int) << endl;
  cout << "sizeof(float): " << sizeof(float) << endl;
  cout << "sizeof(long): " << sizeof(long) << endl;
  cout << "sizeof(char *): " << sizeof(char *) << endl;

  cout << endl;

  cout << "sizeof(FooStatic): " << sizeof(FooStatic) << endl;
  cout << "sizeof(FooOrder): " << sizeof(FooOrder) << endl;
  cout << "sizeof(FooOrder2): " << sizeof(FooOrder2) << endl;

  cout << endl;

  FooOrder obj;
  cout << "Foo: " << &obj << endl;
  cout << "Foo.mem1_: " << &obj.mem1_ << endl;
  cout << "Foo.mem2_: " << &obj.mem2_ << endl;
  cout << "Foo.mem3_: " << &obj.mem3_ << endl;
  cout << "Foo.mem4_: " << &obj.mem4_ << endl;
  cout << "Foo.mem5_: " << &obj.mem5_ << endl;
  cout << "Foo.mem6_: " << &obj.mem6_ << endl;
  cout << "offsetof(Foo.mem1_): " << offsetof(struct FooOrder, mem1_) << endl;
  cout << "offsetof(Foo.mem2_): " << offsetof(struct FooOrder, mem2_) << endl;
  cout << "offsetof(Foo.mem6_): " << offsetof(struct FooOrder, mem6_) << endl;

  cout << endl;

  cout << "sizeof(Base): " << sizeof(Base) << endl;
  cout << "sizeof(Derived): " << sizeof(Derived) << endl;

  cout << endl;

  cout << "sizeof(BaseClass): " << sizeof(BaseClass) << endl;
  cout << "sizeof(DerivedClass): " << sizeof(DerivedClass) << endl;

  cout << endl;
  cout << "sizeof(ABase): " << sizeof(ABase) << endl;
  cout << "sizeof(BBase): " << sizeof(BBase) << endl;
  cout << "sizeof(CBase): " << sizeof(CBase) << endl;
  cout << "sizeof(DBase): " << sizeof(DBase) << endl;

  return 0;
}

#include <iostream>

// 引用计数指的是，所有管理同一个裸指针（raw
// pointer）的shared_ptr，都共享一个引用计数器，
// 每当一个shared_ptr被赋值（或拷贝构造）给其它shared_ptr时，这个共享的引用计数器就加1，
// 当一个shared_ptr析构或者被用于管理其它裸指针时，这个引用计数器就减1，如果此时发现引用计数器为0，
// 那么说明它是管理这个指针的最后一个shared_ptr了，于是我们释放指针指向的资源

// 用shared_ptr，不用new
// 使用weak_ptr来打破循环引用
// 用make_shared来生成shared_ptr
// 用enable_shared_from_this来使一个类能获取自身的shared_ptr

template <class T>
class smart_ptr {
  T* m_ptr;
  uint32_t* m_refCount;

 public:
  smart_ptr(T* ptr = nullptr) : m_ptr(ptr) {
    if (m_ptr)
      m_refCount = new uint32_t(1);
    else
      m_refCount = nullptr;
  }

  ~smart_ptr() {
    if (m_refCount != nullptr) {
      (*m_refCount)--;
      if ((*m_refCount) == 0) {
        delete m_ptr;
        delete m_refCount;
      }
    }
  }
  // Copy constructor
  smart_ptr(const smart_ptr& a) {
    m_ptr = a.m_ptr;
    m_refCount = a.m_refCount;
    (*m_refCount)++;
  }

  // Move constructor
  smart_ptr(smart_ptr&& a) : m_ptr(a.m_ptr), m_refCount(a.m_refCount) {
    a.m_ptr = nullptr;
    a.m_refCount = nullptr;
  }

  // Copy assignment
  smart_ptr& operator=(const smart_ptr& a) {
    m_ptr = a.m_ptr;
    m_refCount = a.m_refCount;
    (*m_refCount)++;
    return *this;
  }

  // Move assignment
  smart_ptr& operator=(smart_ptr&& a) {
    if (&a == this) return *this;
    delete m_ptr;
    delete m_refCount;
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
    m_refCount = a.m_refCount;
    a.m_refCount = nullptr;
    return *this;
  }

  T& operator*() const {
    return *m_ptr;
  }

  T* operator->() const {
    return m_ptr;
  }
};

class Resource {
 public:
  Resource() {
    std::cout << "Resource acquired\n";
  }
  ~Resource() {
    std::cout << "Resource destroyed\n";
  }
};

smart_ptr<Resource> func(smart_ptr<Resource> temp) {
  // Do something
  return temp;
}

int main() {
  Resource* res = new Resource;
  smart_ptr<Resource> ptr1(res);
  {
    smart_ptr<Resource> ptr2(ptr1);
    auto ptr3 = func(ptr1);
    std::cout << "Killing one shared pointer\n";
  }
  std::cout << "Killing another shared pointer\n";
  return 0;
}

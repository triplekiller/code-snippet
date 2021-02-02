template<class T>
class smart_ptr
{
    T* m_ptr;
    uint32_t *m_refCount;
public:
    smart_ptr(T* ptr = nullptr):m_ptr(ptr)
    {
        if(m_ptr)
            m_refCount = new uint32_t(1);
        else
            m_refCount = nullptr;    
    }
    ~smart_ptr()
    {
        if(m_refCount != nullptr){
            (*m_refCount)--;
            if((*m_refCount) == 0){
                delete m_ptr;
                delete m_refCount;
            }
        } 
    }
    // Copy constructor
    smart_ptr(const smart_ptr& a)
    {
        m_ptr = a.m_ptr;
        m_refCount = a.m_refCount;
        (*m_refCount)++;
    }
    // Move constructor
    smart_ptr(smart_ptr&& a): m_ptr(a.m_ptr), m_refCount(a.m_refCount)
    {
        a.m_ptr = nullptr;
        a.m_refCount = nullptr;
    }
    // Copy assignment
    smart_ptr& operator=(const smart_ptr& a)
    {
        m_ptr = a.m_ptr;
        m_refCount = a.m_refCount;
        (*m_refCount)++;
        return *this;
    }
    // Move assignment
    smart_ptr& operator=(smart_ptr&& a)
    {
        if (&a == this)
            return *this;
        delete m_ptr;
        delete m_refCount;
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        m_refCount = a.m_refCount;
        a.m_refCount = nullptr;
        return *this;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};
class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};
smart_ptr<Resource> func(smart_ptr<Resource> temp) 
{
  // Do something
  return temp;
}
int main()
{
    Resource *res = new Resource;
    smart_ptr<Resource> ptr1(res);
    {
        smart_ptr<Resource> ptr2(ptr1); 
            auto ptr3 = func(ptr1);     
        std::cout << "Killing one shared pointer\n";    
    }
    std::cout << "Killing another shared pointer\n";
    return 0;
}

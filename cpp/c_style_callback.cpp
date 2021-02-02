#include <utility>
#include <iostream>

/**
 * Trampolines to methods for C-style callbacks.
 *
 * The void* / callback data is the instance you want the method
 * called on.
 */
template<typename T, typename ...Types>
struct trampoline {
    /**
     * Trampoline for callbacks with void* argument at the end of the
     * argument list
     */
    template<void (T::*ptmf)(Types...)>
    static
    void postvoid(Types... args, void *object) {
	T *o = static_cast<T*>(object);
	(o->*ptmf)(std::forward<Types>(args)...);
    }

    /**
     * Trampoline for callbacks with void* as the first argument
     */
    template<void (T::*ptmf)(Types...)>
    static
    void prevoid(void *object, Types... args) {
	T *o = static_cast<T*>(object);
	(o->*ptmf)(std::forward<Types>(args)...);
    }
};
 
void c_style_callback_caller(void (*cb)(int, void*), void *data)
{
    cb(42, data);
}

void c_style_callback_caller_pre(void (*cb)(void*, int), void *data)
{
    cb(data, 41);
}
 
class C {
public:
    void p0() {
	std::cout << "p0()\n";
    }
 
    void p1(int x) {
	std::cout << "p1(" << x << ")\n";
    }
 
    static
    void classic_cb_p1(int x, void *object) {
	C *c = static_cast<C*>(object);
	c->p1(x);
    }
};
 
int main() {
    C inst;
 
    // both produce EXACTLY the same code
    c_style_callback_caller(trampoline<C, int>::postvoid<&C::p1>, &inst);
    c_style_callback_caller(&C::classic_cb_p1, &inst);

    // also supports void* as the first argument
    c_style_callback_caller_pre(trampoline<C, int>::prevoid<&C::p1>, &inst);

    // special case: no parameters on callback means postvoid and
    // prevoid are identical
    trampoline<C>::postvoid<&C::p0>(&inst);
    trampoline<C>::prevoid<&C::p0>(&inst);

    return 0;
}

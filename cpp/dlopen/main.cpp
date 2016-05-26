/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/11/2015 09:07:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <dlfcn.h>

int main()
{
	using std::cout;
	using std::cerr;

	cout << "C++ dlopen demo\n";

	void *handle = dlopen("./hello.so", RTLD_LAZY);
	if (!handle) {
		cerr << "Cannot open lib: " << dlerror() << std::endl;
		return -1;
	}

	cout << "Loading symbol hello\n";
	typedef void (*func)();

	dlerror();

	func hell = (func)dlsym(handle, "hello");
	const char *dlsym_err = dlerror();
	if (dlsym_err) {
		cerr << "Cannot load symbol hello: " << dlsym_err << '\n';
		dlclose(handle);
		return -1;
	}

	cout << "Calling hello..." << std::endl;
	hell();

	cout << "Close lib...\n";
	dlclose(handle);

	return 0;
}

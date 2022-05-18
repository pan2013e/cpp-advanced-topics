#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <vector>

using namespace std;

void type_to_name(const type_info& ti)
{
    char* realname = abi::__cxa_demangle(ti.name(), 0, 0, 0);
    cout << realname << endl;
    free(realname);
}

class Base {
public:
    virtual ~Base() {}
};

class A : public Base {
public:
    A() {}
};


int main() {
    A a;
    Base* b = &a;
    long* vtable_ptr = (long*)(*(long*)b);
    char* s = (type_info*)(vtable_ptr - 1);
    return 0;
}
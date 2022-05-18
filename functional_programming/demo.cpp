#include <iostream>
#include <vector>
#include <cxxabi.h>

#include "high_order_func.h"
#include "currying.h"
#include "pipeline.h"
#include "operators.h"

using namespace std;

const char* type_to_name(const type_info& ti) {
    return abi::__cxa_demangle(ti.name(), 0, 0, 0);
}

void vector_example() {
    vector<int> a = { 1,2,3,4,5 };
    cout << "vector before map" << endl;
    map<int>(Unary<int>::print, a);
    a = map<int>(Unary<int>::square, a);
    cout << "vector after map" << endl;
    forEach(a.begin(), a.end(), Unary<int>::print); // equivalent to map(Unary<int>::print, a);
}

void high_order_add_example() {
    cout << "type of add(1) is " << type_to_name(typeid(add(1))) << endl;
    cout << "add(15)(25) = " << add(15)(25) << endl;
}

void high_order_binary_example() {
    cout << binary(10, 10, Binary<int>::multiply) << endl;
}

void map_reduce_example() {
    vector<int> a = { 1,2,3,4,5 };
    cout << "map" << endl;
    map<int>(Unary<int>::print, a);
    cout << "reduce" << endl;
    cout << reduce<int>(Binary<int>::multiply, a) << endl;
}

void filter_example() {
    vector<int> a = { 1,2,3,4,5,6,7,8,9,10 };
    cout << "filter" << endl;
    a = filter<int>([](int x) { return x % 2 == 0; }, a);
    map<int>(Unary<int>::print, a);
}

void pipeline_example() {
    cout << "pipeline" << endl;
    int t = 2;
    t = t | [](int x) { return x * x; } | [](int x) { return x + 1; };
    cout << t << endl;
}

int main() {
    vector_example();
    cout << "===========================" << endl;
    high_order_add_example();
    cout << "===========================" << endl;
    high_order_binary_example();
    cout << "===========================" << endl;
    map_reduce_example();
    cout << "===========================" << endl;
    filter_example();
    cout << "===========================" << endl;
    pipeline_example();
    return 0;
}
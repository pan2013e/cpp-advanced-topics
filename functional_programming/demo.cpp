#include <iostream>
#include <vector>
#include <cxxabi.h>

#include "high_order_func.h"
#include "currying.h"
#include "operators.h"

using namespace std;

GET_CITIZEN(square)
GET_CITIZEN(print)
GET_CITIZEN(plus)
GET_CITIZEN(minus)
GET_CITIZEN(multiply)
GET_CITIZEN(divide)

const char* type_to_name(const type_info& ti) {
    return abi::__cxa_demangle(ti.name(), 0, 0, 0);
}

void vector_example() {
    vector<int> a = { 1,2,3,4,5 };
    cout << "vector before map" << endl;
    map(print, a);
    a = map(square, a);
    cout << "vector after map" << endl;
    forEach(a.begin(), a.end(), print); // equivalent to map(Unary::print<int>, a);
}

void high_order_add_example() {
    cout << "type of add(1) is " << type_to_name(typeid(add(1))) << endl;
    cout << "add(15)(25) = " << add(15)(25) << endl;
}

void high_order_binary_example() {
    cout << binary(10, 10, multiply) << endl;
}

void map_reduce_example() {
    vector<int> a = { 1,2,3,4,5 };
    cout << "map" << endl;
    map(print, a);
    cout << "reduce" << endl;
    cout << reduce(multiply, a) << endl;
}

void filter_example() {
    vector<int> a = { 1,2,3,4,5,6,7,8,9,10 };
    cout << "filter" << endl;
    a = filter([](int x) { return x % 2 == 0; }, a);
    map(print, a);
}

void pipeline_example() {
    "pipeline" | print;
    range(1, 6) | reduce<int>(multiply) | print;
}

int factorial(int n) {
    return !n ? 1 : range(1, n + 1) | reduce<int>(multiply);
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
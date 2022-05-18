#pragma once

#include <iostream>

template<class T>
struct Unary {
    static void square(T& p) {
        p = p * p;
    }

    static void print(T& x) {
        std::cout << x << std::endl;
    }

};

template<class T>
struct Binary {
    static T plus(T a, T b) {
        return a + b;
    }
    static T minus(T a, T b) {
        return a - b;
    }
    static T multiply(T a, T b) {
        return a * b;
    }
    static T divide(T a, T b) {
        return a / b;
    }
};
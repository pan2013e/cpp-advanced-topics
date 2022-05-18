#pragma once

#include <functional>

template<class T>
T add(T a, T b) {
    return a + b;
}

template<class T, class F = std::function<T(T)>>
F add(T a) {
    return [a] (T b) {
        return add(a, b);
    };
}

template<class T, class F = std::function<T(T,T)>>
T binary(T a, T b, F op) {
    return op(a, b);
}

template<class T, class F = std::function<T(T)>>
F binary(T a) {
    return [a](T b) {
        return binary(a, b);
    };
}
#pragma once

#include <iostream>
#include <functional>

class tfn_base {};

#define MAKE_CITIZEN(name, ns) \
    class tfn_##name : public tfn_base { \
    public: \
        template<class... Args> \
        auto operator()(Args&&... args) const -> decltype(ns::name(std::forward<Args>(args)...)) { \
            return ns::name(std::forward<Args>(args)...); \
        } \
    };

#define GET_CITIZEN(name) tfn_##name name;

#define REGISTER_UNARY_FUNC(name, arg_name, body) \
    template<class T> \
    static T name(T& arg_name) { \
        body \
    } \
    template<class T> \
    static T& name(T&& arg_name) { \
        body \
    } \

#define REGISTER_BINARY_FUNC(name, arg1, arg2, body) \
    template<class T> \
    static T name(T& arg1, T& arg2) { \
        body \
    } \
    template<class T> \
    static T& name(T&& arg1, T&& arg2) { \
        body \
    } \

template<class T, class F>
auto operator|(T&& a, const F& b) -> decltype(b(a)) {
    return b(std::forward<T>(a));
}

namespace Unary {
    REGISTER_UNARY_FUNC(square, x, return x *= x;)
    REGISTER_UNARY_FUNC(print, x, std::cout << x << std::endl; return x;)
    REGISTER_UNARY_FUNC(id, x, return x;)
    REGISTER_UNARY_FUNC(succ, x, return ++x;)

};

MAKE_CITIZEN(square, Unary)
MAKE_CITIZEN(print, Unary)
MAKE_CITIZEN(id, Unary)
MAKE_CITIZEN(succ, Unary)

namespace Binary {
    REGISTER_BINARY_FUNC(plus, x, y, return x += y;)
    REGISTER_BINARY_FUNC(minus, x, y, return x -= y;)
    REGISTER_BINARY_FUNC(multiply, x, y, return x *= y;)
    REGISTER_BINARY_FUNC(divide, x, y, return x /= y;)
};

MAKE_CITIZEN(plus, Binary)
MAKE_CITIZEN(minus, Binary)
MAKE_CITIZEN(multiply, Binary)
MAKE_CITIZEN(divide, Binary)
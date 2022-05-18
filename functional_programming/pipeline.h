#pragma once

#include <functional>

template<class T, class F>
auto operator|(T&& a, const F& b) -> decltype(b(std::forward<T>(a))) {
    return b(std::forward<T>(a));
}
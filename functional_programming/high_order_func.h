#pragma once

#include <vector>
#include <type_traits>

template<class T>
std::vector<T> range(T begin, T end) {
    begin >= end ? std::__throw_range_error("expected begin < end"), 0 : 0;
    std::vector<T> ret;
    for (T i = begin; i < end; i = i + 1) {
        ret.push_back(i);
    }
    return ret;
}

template<class Iterator, class F>
void forEach(Iterator begin, Iterator end, F callback) {
    for (; begin != end; ++begin) {
        callback(*begin);
    }
}

template<class T, class F>
std::vector<T> map(F callback, std::vector<T> iterable) {
    std::vector<T> ret = iterable;
    forEach(ret.begin(), ret.end(), callback);
    return ret;
}

template<class T, class F>
std::function<std::vector<T>(std::vector<T>)> map(F callback) {
    return [callback](std::vector<T> iterable) {
        return map(callback, iterable);
    };
}

template<class T, class F>
T reduce(F callback, std::vector<T> iterable) {
    T ret = iterable.front();
    forEach(iterable.begin() + 1, iterable.end(), [&ret, callback] (T x) {
        ret = callback(ret, x);
    });
    return ret;
}

template<class T, class F>
std::function<T(std::vector<T>)> reduce(F callback) {
    return [callback](std::vector<T> iterable) {
        return reduce(callback, iterable);
    };
}

template<class T, class F>
T reduce(F callback, std::vector<T> iterable, T init) {
    T ret = init;
    forEach(iterable.begin(), iterable.end(), [&ret, callback] (T x) {
        ret = callback(ret, x);
    });
    return ret;
}

template<class T, class F>
std::function<T(std::vector<T>)> reduce(F callback, T init) {
    return [callback, init](std::vector<T> iterable) {
        return reduce(callback, iterable, init);
    };
}

template<class T, class F>
std::vector<T> filter(F callback, std::vector<T> iterable) {
    std::vector<T> ret;
    forEach(iterable.begin(), iterable.end(), [&ret, callback] (T x) {
        if (callback(x)) {
            ret.push_back(x);
        }
    });
    return ret;
}
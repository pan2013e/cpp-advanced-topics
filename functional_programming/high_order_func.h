#pragma once

#include <vector>
#include <type_traits>

template<class Iterator, class F>
void forEach(Iterator begin, Iterator end, F callback) {
    for (; begin != end; ++begin) {
        callback(*begin);
    }
}

template<class T, class F, class Iterable = std::vector<T>>
Iterable map(F callback, Iterable iterable) {
    Iterable ret = iterable;
    forEach(ret.begin(), ret.end(), callback);
    return ret;
}

template<class T, class F, class Iterable = std::vector<T>>
T reduce(F callback, Iterable iterable) {
    T ret = iterable.front();
    forEach(iterable.begin() + 1, iterable.end(), [&ret, callback] (T x) {
        ret = callback(ret, x);
    });
    return ret;
}

template<class T, class F, class Iterable = std::vector<T>>
T reduce(F callback, Iterable iterable, T init) {
    T ret = init;
    forEach(iterable.begin(), iterable.end(), [&ret, callback] (T x) {
        ret = callback(ret, x);
    });
    return ret;
}

template<class T, class F, class Iterable = std::vector<T>>
Iterable filter(F callback, Iterable iterable) {
    Iterable ret;
    forEach(iterable.begin(), iterable.end(), [&ret, callback] (T x) {
        if (callback(x)) {
            ret.push_back(x);
        }
    });
    return ret;
}
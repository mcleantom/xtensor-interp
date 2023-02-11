#ifndef XTENSOR_INTERP_ITERTOOLS_H
#define XTENSOR_INTERP_ITERTOOLS_H

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

template<class A, class B>
std::vector<std::tuple<A, B>> product(const std::vector<A>& a, const std::vector<B>& b) {
    std::vector<std::tuple<A, B>> res(size(a)*size(b));
    auto i = begin(res);
    std::for_each(
        cbegin(a),
        cend(a),
        [&](const auto& a_) {
            std::for_each(
                cbegin(b),
                cend(b),
                [&](const auto& b_) {
                    *i++ = {a_, b_};
                }
            );
        }
    );

    return res;
};

template<class T>
std::vector<std::vector<T>> cart_product (const std::vector<std::vector<T>>& v) {
    std::vector<std::vector<T>> s = {{}};
    for (const auto& u : v) {
        std::vector<std::vector<T>> r;
        for (const auto& x : s) {
            for (const auto y : u) {
                r.push_back(x);
                r.back().push_back(y);
            }
        }
        s = std::move(r);
    }
    return s;
}

#endif
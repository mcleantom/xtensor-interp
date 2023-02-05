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

#endif
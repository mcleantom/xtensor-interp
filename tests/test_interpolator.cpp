#include "XTensorInterp/interpolator.h"
#include <gtest/gtest.h>
#include <iostream>
#include <xtensor/xarray.hpp>

TEST(Interpolator, Regular1D)
{
    auto x = Regular<double>(1, 3, 3);
    xt::xarray<double> data = { 3, 2, 0 };
    Interpolator<double> interp(x, data);
    auto res = interp({1, 1.5, 2.72});
    xt::xarray<double> expected = { 3, 2.5, 0.56};
    for (size_t i=0; i<res.size(); ++i) {
        EXPECT_FLOAT_EQ(res[i], expected[i]);
    }
}
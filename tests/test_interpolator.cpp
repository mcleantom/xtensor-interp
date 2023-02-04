#include "XTensorInterp/interpolator.h"
#include <gtest/gtest.h>
#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor/xnpy.hpp>

TEST(Interpolator, Regular1D)
{
    double min = 0;
    double max = 3;
    int n = 3;
    auto xarr = xt::linspace<double>(min, max, n);
    auto xcoord = Regular<double>(min, max, n);
    auto yarr = xt::eval(2*xarr);
    
    auto xin = xt::linspace(min, max, n*3);

    Interpolator<double> interp(xcoord, yarr);
    auto interpolator_res = interp(xin);

    auto xt_res = xt::eval(xt::interp(xin, xarr, yarr));

    ASSERT_EQ(xt_res.size(), interpolator_res.size());
    ASSERT_EQ(interpolator_res.size(), xin.size());

    for (size_t i=0; i<interpolator_res.size(); ++i) {
        EXPECT_EQ(interpolator_res[i], xt_res[i]);
    }
}
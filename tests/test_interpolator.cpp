#include "XTensorInterp/interpolator.h"

#include <gtest/gtest.h>
#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp>
#include <xtensor/xnpy.hpp>

TEST(Interpolator, Regular1D)
{
    // double min = 0;
    // double max = 3;
    // int n = 3;
    // auto xarr = xt::linspace<double>(min, max, n);
    // std::unique_ptr<Container<double>> xcoord = std::make_unique<Regular<double>>(min, max, n);
    // auto yarr = xt::eval(2*xarr);
    // auto xin = xt::linspace(min, max, n*3);
    // std::vector<std::unique_ptr<Container<double>>> grid;
    // grid.push_back(std::move(xcoord));
    // Interpolator<double> interp(std::move(grid), yarr);
    // auto interpolator_res = interp(xin);

    // auto xt_res = xt::eval(xt::interp(xin, xarr, yarr));

    // ASSERT_EQ(xt_res.size(), interpolator_res.size());
    // ASSERT_EQ(interpolator_res.size(), xin.size());

    // for (size_t i=0; i<interpolator_res.size(); ++i) {
    //     EXPECT_EQ(interpolator_res[i], xt_res[i]);
    // }
}

TEST(Interpolator, Regular2D)
{
    // size_t m = 10;
    // size_t n = 20;
    // std::vector<std::unique_ptr<Container<double>>> grid;
    // grid.push_back(std::move(std::make_unique<Regular<double>>(0, 10, m)));
    // grid.push_back(std::move(std::make_unique<Regular<double>>(0, 10, n)));

    // xt::xarray<double> x = xt::linspace<double>(0, 10, m);
    // xt::xarray<double> y = xt::linspace<double>(0, 10, n);

    // x.reshape({m, 1});
    // y.reshape({1, n});

    // auto data = xt::eval(x*y);
    // data.reshape({m, n});

    // Interpolator<double> interp(std::move(grid), data);

    // // xt::xarray<double> a0 = xt::linspace(0, 10, 15);
    // // xt::xarray<double> b0 = xt::linspace(0, 10, 15);
    // // auto xin = xt::vstack(xt::xtuple(a0, b0));

    // xt::xarray<double> xin2 = {
    //     {2.1, 6.2, 8.3},
    //     {3.3, 5.2, 7.1}
    // };

    // interp(xin2);
}

auto f(xt::xarray<double> x, xt::xarray<double> y, xt::xarray<double> z) {
    return 2 * xt::pow(x, 3) + 3 * xt::pow(y, 2) - z;
}

TEST(Interpolator, Regular3D)
{
    std::vector<std::unique_ptr<Container<double>>> grid;
    grid.emplace_back(new Regular<double>(1, 4, 11));
    grid.emplace_back(new Regular<double>(4, 7, 22));
    grid.emplace_back(new Regular<double>(7, 9, 33));

    auto x = xt::linspace<double>(1, 4, 11);
    auto y = xt::linspace<double>(4, 7, 22);
    auto z = xt::linspace<double>(7, 9, 33);

    auto [xg, yg, zg] = xt::meshgrid(x, y, z);
    auto data = xt::eval(f(xg, yg, zg));

    Interpolator interp(std::move(grid), data);

    xt::xarray<double> x_in = {
        {2.1, 6.2, 8.3},
        {3.3, 5.2, 7.1}
    };

    auto rtn = interp(x_in);

    xt::xarray<double> expected = { 125.80469388,  146.30069388};

    EXPECT_TRUE(xt::allclose(rtn, expected, 1e-5));
}
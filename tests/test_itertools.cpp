#include "XTensorInterp/itertools.h"
#include <gtest/gtest.h>
#include <boost/mp11.hpp>

TEST(Itertools, Product)
{
    std::vector<char> A = {'a', 'b', 'c'};
    std::vector<int> B = {1, 2, 3};
    auto res = product(A, B);
    EXPECT_EQ(res.size(), A.size()*B.size());
    
    std::tuple<char, int> expected = {'a', 1};
    EXPECT_EQ(res[0], expected);

    expected = {'a', 2};
    EXPECT_EQ(res[1], expected);

    expected = {'a', 3};
    EXPECT_EQ(res[2], expected);

    expected = {'c', 2};
    EXPECT_EQ(res[res.size()-2], expected);

    expected = {'c', 3};
    EXPECT_EQ(res[res.size()-1], expected);
}
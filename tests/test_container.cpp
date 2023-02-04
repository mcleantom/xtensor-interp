#include "XTensorInterp/container.h"
#include <gtest/gtest.h>

TEST(Container, Regular)
{
    std::vector<float> vals = {0, 1, 2, 3, 4, 5};
    float min = vals[0];
    float max = vals[vals.size()-1];
    float steps = vals.size();
    Regular<float> container(min, max, steps);
    EXPECT_EQ(container.minValue(), min);
    EXPECT_EQ(container.maxValue(), max);
    EXPECT_EQ(container.size(), steps);

    for (size_t i=0; i<vals.size(); ++i) {
        EXPECT_EQ(container.findIndex(vals[i], false), i);
    }

    EXPECT_EQ(container.findIndex(1.25, true), 1);
    EXPECT_EQ(container.findIndex(1.5, true), 1);
    EXPECT_EQ(container.findIndex(1.75, true), 1);

    // If we are unbouded and we extrapolate, get the min and max indices
    EXPECT_EQ(container.findIndex(2, false), 2);
    EXPECT_EQ(container.findIndex(min, false), 0);
    EXPECT_EQ(container.findIndex(min-0.01, false), 0);
    EXPECT_EQ(container.findIndex(max, false), steps-1);
    EXPECT_EQ(container.findIndex(max+0.01, false), steps-1);
    
    // If we are bounded, return -1
    EXPECT_EQ(container.findIndex(min, true), 0);
    EXPECT_EQ(container.findIndex(min-10, true), -1);
    EXPECT_EQ(container.findIndex(max, true), steps-1);
    EXPECT_EQ(container.findIndex(max+10, true), -1);
}
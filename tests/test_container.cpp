#include "XTensorInterp/container.h"
#include <gtest/gtest.h>

TEST(Container, Regular)
{
    float min = -10;
    float max = 10;
    float steps = 11;
    Regular<float> container(min, max, steps);
    EXPECT_EQ(container.minValue(), min);
    EXPECT_EQ(container.maxValue(), max);
    EXPECT_EQ(container.size(), steps);

    // If we are unbouded and we extrapolate, get the min and max indices
    EXPECT_EQ(container.findIndex(0, false), 5);
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
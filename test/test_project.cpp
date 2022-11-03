#include <iostream>
#include "gtest/gtest.h"
#include "axis.h"
#include <string>


TEST(AxisMethod, DoesInitialize) {
	float min = 0;
	float max = 10;
	float step = 2;
	std::string name = "x";
	Axis axis(name, min, max, step);
}

TEST(AxisMethod, DoesGetIndex) {
	float min = 0;
	float max = 10;
	float step = 2;
	std::string name = "x";
	Axis axis(name, min, max, step);

	int index = axis.get_index(0);
	EXPECT_EQ(0, 0);
	EXPECT_EQ(0, axis.get_index(1));
	EXPECT_EQ(1, axis.get_index(2));
}

TEST(AxisMethod, DoesThrowException) {
	float min = 0;
	float max = 10;
	float step = 2;
	std::string name = "x";
	Axis axis(name, min, max, step);

	EXPECT_THROW(axis.get_index(-1), std::out_of_range);
}
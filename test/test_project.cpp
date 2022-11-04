#include <iostream>
#include "gtest/gtest.h"
#include "axis.h"
#include "rgi.h"
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

TEST(RGIClass, WrongNumAxis) {
	std::map<std::string, Axis> axis{
		{"X", Axis("X", 0, 10, 2)},
		{"Y", Axis("Y", -10, 0, 1)}
	};
	xt::xarray<double> data{ 1, 2, 3 };
	
	EXPECT_THROW(RGI(axis, data), std::invalid_argument);

	data = { {1, 2, 3}, {4, 5, 6} };
	EXPECT_NO_THROW(RGI(axis, data));
}
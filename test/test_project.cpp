#include <iostream>
#include "gtest/gtest.h"
#include "coodinates_map.h"
#include "rgi.h"
#include <string>


TEST(AxisMethod, DoesInitialize) {
	float min = 0;
	float max = 10;
	float step = 2;
	std::string name = "x";
	CoordinatesMap axis(name, min, max, step);
}

TEST(AxisMethod, DoesGetIndex) {
	float min = 0;
	float max = 10;
	float step = 2;
	std::string name = "x";
	CoordinatesMap axis(name, min, max, step);

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
	CoordinatesMap axis(name, min, max, step);

	EXPECT_THROW(axis.get_index(-1), std::out_of_range);
}


TEST(RGIClass, Initializes) {
	std::map<std::string, CoordinatesMap> axis{
		{"X", CoordinatesMap("X", 0, 10, 2)}
	};

	xt::xarray<double> data = { 0, 2, 4, 6, 8, 10 };
	RGI x(axis, data);

}
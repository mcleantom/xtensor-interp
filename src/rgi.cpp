#include "rgi.h"
#include "axis.h"
#include <vector>
#include <xtensor/xarray.hpp>
#include <map>
#include <string>
#include <stdexcept>

RGI::RGI(std::map<std::string, Axis> axis, xt::xarray<double> data) {
	if (axis.size() != data.dimension()) {
		throw std::invalid_argument("The number of axis must match the dimensions of the data.");
	}

	this->axis = axis;
	this->data = data;
}

xt::xarray<double> RGI::linear(std::map<std::string, Axis> axis) {
	return xt::xarray<double> {1, 2, 3};
}
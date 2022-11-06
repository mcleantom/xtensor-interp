#include "rgi.h"
#include "coodinates_map.h"
#include <vector>
#include <xtensor/xarray.hpp>
#include <map>
#include <string>
#include <stdexcept>
#include <xtensor/xview.hpp>

RGI::RGI(std::map<std::string, CoordinatesMap> axis, xt::xarray<double> data) {
	this->axis = axis;
	this->data = data;
}

xt::xarray<double> RGI::linear(std::map<std::string, xt::xarray<double>> axis) {
	xt::xarray<double> result;
	auto interp_grid = xt::zeros<double>({ this->axis.size(), axis.begin()->second.shape(0) });

	// Initialize the interp grid in the same order as the axis
	int counter = 0;
	for (auto it = this->axis.begin(); it != this->axis.end(); it++) {
		auto row = xt::view(interp_grid, counter, xt::all());
		//row = axis[it->first];
	}

	return xt::xarray<double> {1, 2, 3};
}


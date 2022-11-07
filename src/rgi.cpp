#include "rgi.h"
#include "coodinates_map.h"
#include <vector>
#include <map>
#include <string>
#include <xtensor/xarray.hpp>
#include <xtensor/xview.hpp>


RGI::RGI(std::map<std::string, CoordinatesMap> axis, xt::xarray<double> data) {
	this->axis = axis;
	this->data = data;
}

xt::xarray<double> RGI::linear(std::map<std::string, xt::xarray<double>> axis) {
	xt::xarray<double> result;
	auto& interp_grid = axis.find(this->axis.begin()->first)->second;

	// Initialize the interp grid in the same order as the axis
	int counter = 0;
	for (auto it = std::next(this->axis.begin(), 1); it != this->axis.end(); it++) {
		interp_grid = xt::vstack(xt::xtuple(interp_grid, axis.find(it->first)->second));
	}
	
	// y = y + (x-x1)*(y2-y1)/(x2-x1)
	for (auto x1 = interp_grid.begin(), x1 != interp_grid.end(); x1++) {

	}


	return xt::xarray<double> {1, 2, 3};
}


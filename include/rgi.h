#ifndef XTENSOR_INTERP_RGI_H
#define XTENSOR_INTERP_RGI_H

#include "axis.h"
#include <vector>
#include <xtensor/xarray.hpp>

class RGI {
public:
	RGI(std::map<std::string, Axis> axis, xt::xarray<double> data);
	xt::xarray<double> linear(std::map<std::string, Axis> axis);
private:
	std::map<std::string, Axis> axis;
	xt::xarray<double> data;
};

#endif
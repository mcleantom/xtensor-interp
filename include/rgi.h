#ifndef XTENSOR_INTERP_RGI_H
#define XTENSOR_INTERP_RGI_H

#include "axis.h"
#include <vector>
#include <xtensor/xarray.hpp>

class RGI {
public:
	RGI(std::vector<Axis> axis, xt::xarray<double> data);
private:
	std::vector<Axis> axis;
	xt::xarray<double> data;
};

#endif
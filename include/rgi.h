#ifndef XTENSOR_INTERP_RGI_H
#define XTENSOR_INTERP_RGI_H

#include "coodinates_map.h"
#include <vector>
#include <xtensor/xarray.hpp>
#include <map>

class RGI {
public:
	RGI(std::map<std::string, CoordinatesMap> axis, xt::xarray<double> data);
	xt::xarray<double> linear(std::map<std::string, CoordinatesMap> axis);
private:
	xt::xarray<double> linear(std::map<std::string, xt::xarray<double>> axis);
	std::map<std::string, CoordinatesMap> axis;
	xt::xarray<double> data;
};

#endif
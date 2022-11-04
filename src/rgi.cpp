#include "rgi.h"
#include "axis.h"
#include <vector>
#include <xtensor/xarray.hpp>


RGI::RGI(std::vector<Axis> axis, xt::xarray<double> data) {
	this->axis = axis;
	this->data = data;
}

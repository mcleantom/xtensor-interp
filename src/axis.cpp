#include "axis.h"
#include <string>
#include <type_traits>
#include <stdexcept>

Axis::Axis(std::string name, float min, float max, float step)
{
	this->name = name;
	this->max = max;
	this->min = min;
	this->step = step;
}

int Axis::get_index(float x) {
	if ((x < this->min) || (x > this->max)) {
		throw std::out_of_range("Must interpolate for value within the grid");
	}
	return ((x - this->min) / this->step);
}
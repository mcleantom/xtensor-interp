#ifndef XTENSOR_INTERP_AXIS_H
#define XTENSOR_INTERP_AXIS_H

#include<string>

class Axis {
public:
	Axis(std::string name, float min, float max, float step);
	int get_index(float x);
protected:
	std::string name;
	float min;
	float max;
	float step;
};

#endif
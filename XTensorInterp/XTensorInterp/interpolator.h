#ifndef XTENSOR_INTERP_INTERPOLATOR_H
#define XTENSOR_INTERP_INTERPOLATOR_H

#include "container.h"
#include "axis.h"
#include <memory.h>
#include <xtensor/xarray.hpp>

template<typename T>
class Interpolator {
public:
    Interpolator(
        Container<T> &x,
        xt::xarray<T> data
    ) 
    : m_x(x)
    , m_Data(std::move(data)) {};
    xt::xarray<T> operator() (const xt::xarray<T>& xarr) {
        auto dims = xarr.shape();
        auto res = xt::empty<T>(dims);
        for (size_t i=0; i<dims[0]; ++i) {
            auto x = xarr[i];
            auto index = m_x.findIndex(x, false);
            auto x1 = m_x.coordinateValue(index);
            auto x2 = m_x.coordinateValue(index+1);
            auto dx = x2-x1;
            auto y1 = m_Data[index];
            auto y2 = m_Data[index+1];
            auto dy = y2-y1;
            auto y = y1 + ((x-x1)*(y2-y1))/(x2-x1);
            res[i] = y;
        }
        return res;
    };
private:
    Container<T>& m_x;
    xt::xarray<T> m_Data;
};

#endif

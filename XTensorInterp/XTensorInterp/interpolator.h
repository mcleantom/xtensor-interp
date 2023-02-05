#ifndef XTENSOR_INTERP_INTERPOLATOR_H
#define XTENSOR_INTERP_INTERPOLATOR_H

#include "container.h"
#include "axis.h"
#include "itertools.h"
#include <memory.h>
#include <utility>
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

        // auto [indices, norm_distances] = find_indices(xarr);

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
    /**
     * @brief Find the lower indices and the norm-distances along the hypercube for x.
     * 
     * @param xi 
     * @return std::tuple<xt::xarray<size_t>, xt::xarray<T>> 
     */
    std::tuple<xt::xarray<size_t>, xt::xarray<T>> find_indices(const xt::xarray<T>& xi) {
        xt::xarray<size_t> indices = xt::empty<size_t>(xi.shape());
        xt::xarray<T> norm_distances = xt::empty<T>(xi.shape());
        for (size_t i=0; i<xi.size(); ++i) {
            auto index = m_x.findIndex(xi[i], false);
            indices[i] = index;
            auto x1 = m_x.coordinateValue(index);
            auto x2 = m_x.coordinateValue(index+1);
            auto dx = x2 - x1;
            auto norm_dist = (xi[i] - x1) / dx;
            norm_distances[i] = norm_dist;
        }
        std::tuple<xt::xarray<size_t>, xt::xarray<T>> rtn = {indices, norm_distances};
        return rtn;
    };

    T evaluate_linear(std::vector<size_t>& indices, std::vector<T>& norm_distances) {
        assert(indices.size() == norm_distances.size());
        /* The formula for linear interpolation in 2D is the form:
            value = m_Data[i0, i1]      * (1-y0)    * (1-y1) +
                    m_Data[i0, i1+1]    * (1-y0)    * y1     +
                    m_Data[i0+1, i1]    * y0        * (1-y1) +
                    m_Data[i0+1, i1+1]  * y0        * y1
        
            Notice how:
                i_n maps to 1-y_n
            and
                i_n+1 maps to y_n
        */

        // First, pre-calculate 1-yn
        size_t n = indices.size();

        std::vector<T> shift_norm_distances;
        std::transform(
            norm_distances.begin(),
            norm_distances.end(),
            shift_norm_distances.begin(),
            std::back_inserter(shift_norm_distances),
            [](auto & x) { return 1-x; }
        );

        // And pre-calculate in + 1
        std::vector<size_t> shift_indices;
        std::transform(
            indices.begin(),
            indices.end(),
            shift_indices.begin(),
            std::back_inserter(shift_norm_distances),
            [](auto & x) { return 1-x; }
        );

        // We pair in to (1 - yn)
        std::vector<std::tuple<size_t, T>> zipped1(n);
        for (size_t i=0; i<indices.size(); ++i) {
            zipped1[i] = { indices[i], shift_norm_distances[i] };
        };

        // and we pair in + 1 to yn
        std::vector<std::tuple<size_t, T>> zipped2(n);
        for (size_t i=0; i<indices.size(); ++i) {
            zipped2[i] = { shift_indices[i], norm_distances[i] };
        };

        // Now map (in, 1-yn) to (in+1, yn)
        std::vector<std::tuple<std::tuple<size_t, T>>> zipped3(n);
        for (size_t i=0; i<zipped1.size(); ++i) {
            zipped3[i] = {zipped1[i], zipped2[i]};
        }

        // Take the cartesian product of zipped1 and zipped2
        auto hypercube = product(zipped1, zipped2);
        for (const auto[edge_indices, weights] : hypercube) {
            
        }
    };

    Container<T>& m_x;
    xt::xarray<T> m_Data;
};

#endif

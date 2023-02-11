#ifndef XTENSOR_INTERP_INTERPOLATOR_H
#define XTENSOR_INTERP_INTERPOLATOR_H

#include "container.h"
#include "axis.h"
#include "itertools.h"
#include <limits>
#include <memory.h>
#include <stdexcept>
#include <utility>
#include <xtensor/xarray.hpp>
#include <xtensor/xview.hpp>
#include <xtensor/xio.hpp>

template<typename T>
class Interpolator {
public:
    Interpolator(
        std::vector<std::unique_ptr<Container<T>>> grid,
        xt::xarray<T> data
    )
    : m_Grid(std::move(grid))
    , m_Data(std::move(data))
    , m_NDIMS(m_Grid.size()) {};

    /**
     * @brief Interpolaton at coordinates
     * 
     * @param xarr xt::xarray of shape (NPOINTS, NDIMS)
     * @return xt::xarray<T> ndarray of shape (NPOINTS, )
     */
    xt::xarray<T> operator() (const xt::xarray<T>& xarr) {
        auto dims = xarr.shape();
        if (dims[1] != m_NDIMS) {
            throw std::invalid_argument("input vector has the wrong number of dimensions");
        }
        auto res = xt::empty<T>({dims[0]});

        for (size_t row=0; row<dims[0]; ++row) {
            auto [indices, norm_distances] = find_indices(xt::row(xarr, row));
            auto res1 = evaluate_linear(indices, norm_distances);
            res.at(row) = res1.at(0);
        }
        
        return res;
    };
private:
    /**
     * @brief Find the indices and norm distances of the points, xi. 
     * 
     * @param xi The coordinates to find, of shape (NUM_DIMS, NUM_POINTS)
     * @return std::tuple<xt::xarray<size_t>, xt::xarray<T>> A tuple of indices and norm distances for each of the 
     points in xi.
     */
    std::tuple<xt::xarray<size_t>, xt::xarray<T>> find_indices(const xt::xarray<T>& xi) {
        assert(xi.shape().size() == 1);
        assert(xi.shape()[0] == m_NDIMS);
        auto shape = xi.shape();
        xt::xarray<size_t> indices = xt::zeros<size_t>(shape);
        xt::xarray<T> norm_distances = xt::zeros<T>(shape);

        for (size_t i=0; i<shape[0]; ++i) {
            std::unique_ptr<Container<T>> &grid = m_Grid[i];
            auto x = xi.at(i);
            auto idx = grid->findIndex(x, false);
            auto x1 = grid->coordinateValue(idx);
            auto x2 = grid->coordinateValue(idx+1);
            auto dx = x2-x1;
            auto norm_dist = (x-x1)/dx;
            indices.at(i) = idx;
            norm_distances.at(i) = norm_dist;
        }

        std::tuple<xt::xarray<size_t>, xt::xarray<T>> rtn = {indices, norm_distances};
        return rtn;
    };
    /**
     * @brief Do linear interpolation.
     * 
     * @param indices an xarray of size_t of shape (NDIMS, NPOINTS)
     * @param norm_distances an xarray of T of shape (NDIMS, NPOINTS)
     * @return T 
     */
    xt::xarray<double> evaluate_linear(xt::xarray<size_t>& indices, xt::xarray<T>& norm_distances) {
        assert(indices.shape() == norm_distances.shape());
        assert(indices.shape()[0] == m_NDIMS);
        // assert(indices.shape().size() == 2);
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

        size_t n = indices.size();

        xt::xarray<T> shift_norm_distances = 1 - norm_distances;    // (1-yn)
        xt::xarray<T> shift_indices = indices + 1;                  // in + 1

        // pair in to 1-yn
        std::vector<std::tuple<size_t, T>> zipped1(n);
        for (size_t i=0; i<indices.size(); ++i) {
            zipped1[i] = { indices[i], shift_norm_distances[i] };
        };

        // pair in+1 to yn
        std::vector<std::tuple<size_t, T>> zipped2(n);
        for (size_t i=0; i<indices.size(); ++i) {
            zipped2[i] = { shift_indices[i], norm_distances[i] };
        };

        xt::xarray<double> value = {0};
        // The binary value at each position will tell us if we should take the value
        // from the first zipped, or the second. i.e. 101 will correspond with
        // {zipped2[0], zipped1[1], zipped2[2]}
        size_t index = 0;
        // Max iterations is when the index is all 1's, i.e. 111. We can calculate this
        // value by finding 1000 and subtracting 1 to make 0111.
        size_t maxIterations = (2<<(m_NDIMS-1));
        xt::xarray<double> val = {0};
        while(index<maxIterations){
            std::vector<std::tuple<size_t, T>> single_product(m_NDIMS);
            for (size_t i=0; i<m_NDIMS; ++i) {
                // We pick the second element if there is a 1 in the index of the index we are looking at
                bool pickSecond = (index >> (m_NDIMS-i-1)) & 1;
                if (pickSecond) {
                    single_product[i] = zipped2[i];
                } else {
                    single_product[i] = zipped1[i];
                }
                continue;
            }

            double weight = 1;
            for (const auto& tup : single_product) {
                weight *= std::get<1>(tup);
            }

            xt::xstrided_slice_vector sv;
            for (size_t i=0; i<m_NDIMS; ++i) {
                sv.push_back(std::get<0>(single_product[i]));
            }

            auto v = xt::strided_view(m_Data, sv);
            auto term = v * weight;
            value = value+term;
            ++index;
        }
        
        return value;
    };
    std::vector<std::unique_ptr<Container<T>>> m_Grid;
    xt::xarray<T> m_Data;
    size_t m_NDIMS;
};

#endif

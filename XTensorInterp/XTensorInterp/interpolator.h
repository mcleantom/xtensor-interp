#ifndef XTENSOR_INTERP_INTERPOLATOR_H
#define XTENSOR_INTERP_INTERPOLATOR_H

#include "container.h"
#include "axis.h"
#include "itertools.h"
#include <limits>
#include <memory.h>
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
        auto res = xt::empty<T>(dims);

        auto [indices, norm_distances] = find_indices(xt::transpose(xarr));

        assert(
            xt::xarray<size_t>({{3, 7}, {15, 8}, {20, 1}}) == indices
        );

        assert(
            xt::amax(xt::xarray<T>({{2.f/3.f, 2.f/3.f}, {0.4, 0.4}, {0.8, 0.6}}) - norm_distances)(0) < 1e-7
        );
        
        auto res1 = evaluate_linear(indices, norm_distances);

        for (size_t i=0; i<dims[0]; ++i) {
            auto x = xarr[i];
            auto index = m_Grid[0]->findIndex(x, false);
            auto x1 = m_Grid[0]->coordinateValue(index);
            auto x2 = m_Grid[0]->coordinateValue(index+1);
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
     * @brief Find the indices and norm distances of the points, xi. 
     * 
     * @param xi The coordinates to find, of shape (NUM_DIMS, NUM_POINTS)
     * @return std::tuple<xt::xarray<size_t>, xt::xarray<T>> A tuple of indices and norm distances for each of the 
     points in xi.
     */
    std::tuple<xt::xarray<size_t>, xt::xarray<T>> find_indices(const xt::xarray<T>& xi) {
        auto shape = xi.shape();
        auto I = shape[0];
        auto J = shape[1];
        xt::xarray<size_t> indices = xt::zeros<size_t>(shape);
        xt::xarray<T> norm_distances = xt::zeros<T>(shape);

        std::cout << "xi: \n" << xi << std::endl;

        for (size_t i=0; i<I; ++i) {
            std::unique_ptr<Container<T>> &grid = m_Grid[i];
            xt::xarray<size_t> ix = xt::zeros<size_t>({J});
            xt::xarray<T> nd = xt::zeros<size_t>({J});

            for (size_t j=0; j<J; ++j) {
                // std::vector<size_t> indexer = {i, j};
                auto x = xi.at(i, j);
                auto idx = grid->findIndex(x, false);
                ix[j] = grid->findIndex(x, false);
                auto x1 = grid->coordinateValue(idx);
                auto x2 = grid->coordinateValue(idx+1);
                auto dx = x2-x1;
                auto norm_dist = (x-x1)/dx;
                nd[j] = norm_dist;
            }

            std::cout << ix << std::endl;
            std::cout << nd << std::endl;

            xt::view(indices, i, xt::all()) = ix;
            xt::view(norm_distances, i, xt::all()) = nd;
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
    T evaluate_linear(xt::xarray<size_t>& indices, xt::xarray<T>& norm_distances) {
        assert(indices.shape() == norm_distances.shape());
        assert(indices.shape()[0] == m_NDIMS);
        assert(indices.shape().size() == 2);
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

        auto hypercube = product(zipped1, zipped2);

        std::cout << "hi2" << std::endl;




        // std::vector<T> shift_norm_distances;
        // std::transform(
        //     norm_distances.begin(),
        //     norm_distances.end(),
        //     shift_norm_distances.begin(),
        //     std::back_inserter(shift_norm_distances),
        //     [](auto & x) { return 1-x; }
        // );

        // And pre-calculate in + 1
        // std::vector<size_t> shift_indices;
        // std::transform(
        //     indices.begin(),
        //     indices.end(),
        //     shift_indices.begin(),
        //     std::back_inserter(shift_norm_distances),
        //     [](auto & x) { return 1-x; }
        // );

        // We pair in to (1 - yn)
        // std::vector<std::tuple<size_t, T>> zipped1(n);
        // for (size_t i=0; i<indices.size(); ++i) {
        //     zipped1[i] = { indices[i], shift_norm_distances[i] };
        // };

        // // and we pair in + 1 to yn
        // std::vector<std::tuple<size_t, T>> zipped2(n);
        // for (size_t i=0; i<indices.size(); ++i) {
        //     zipped2[i] = { shift_indices[i], norm_distances[i] };
        // };

        // // Now map (in, 1-yn) to (in+1, yn)
        // std::vector<std::tuple<std::tuple<size_t, T>>> zipped3(n);
        // for (size_t i=0; i<zipped1.size(); ++i) {
        //     zipped3[i] = {zipped1[i], zipped2[i]};
        // }

        // // Take the cartesian product of zipped1 and zipped2
        // auto hypercube = product(zipped1, zipped2);
        // for (const auto[edge_indices, weights] : hypercube) {
            
        // }
        return 0;
    };
    std::vector<std::unique_ptr<Container<T>>> m_Grid;
    xt::xarray<T> m_Data;
    size_t m_NDIMS;
};

#endif

#ifndef XTENSOR_INTERP_AXIS_HPP
#define XTENSOR_INTERP_AXIS_HPP

#include <memory>
#include "XTensorInterp/container.h"

template<typename T>
class Axis {
public:
    Axis() = default;
    Axis(
        Container<T> container
    ) : m_Container(container) {};
    /**
     * @brief Returns the minmium value held in the axis.
     */
    constexpr T minimum() const { return m_Container->minimum(); };
    /**
     * @brief Returns the maximum value held in the axis.
     */
    constexpr T maximum() const { return m_Container->maximum(); };
    /**
     * @brief Returns the number of values for this axis.
     */
    constexpr T size() const { return m_Container->size(); };
private:
    std::unique_ptr<T> m_Container;
};

#endif
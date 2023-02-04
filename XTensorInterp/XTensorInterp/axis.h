#ifndef XTENSOR_INTERP_AXIS_HPP
#define XTENSOR_INTERP_AXIS_HPP

#include <memory>
#include "container.h"

template<typename T>
class Axis {
public:
    Axis() = default;
    Axis(
       std::unique_ptr<Container<T>> container
    ) : m_Container(container) {};
    /**
     * @brief Returns the minmium value held in the axis.
     */
    T minimum() const { return m_Container->minimum(); };
    /**
     * @brief Returns the maximum value held in the axis.
     */
    T maximum() const { return m_Container->maximum(); };
    /**
     * @brief Returns the number of values for this axis.
     */
    T size() const { return m_Container->size(); };
private:
    std::unique_ptr<Container<T>> m_Container;
};

#endif
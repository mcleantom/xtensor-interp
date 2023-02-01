#ifndef XTENSOR_INTERP_AXIS_HPP
#define XTENSOR_INTERP_AXIS_HPP

template<typename T>
class Axis {
public:
    Axis() = default;
    Axis(
        const T min,
        const T max,
        long int size
    ) : _M_min(min), _M_max(max), _M_size(size) {};
    /**
     * @brief Returns the minmium value held in the axis.
     */
    constexpr T minimum() const { return _M_min; };
    /**
     * @brief Returns the maximum value held in the axis.
     */
    constexpr T maximum() const { return _M_max; };
    /**
     * @brief Returns the number of values for this axis.
     */
    constexpr T size() const { return _M_size; };
private:
    const T _M_min; // The minimum value held by the axis
    const T _M_max; // The maximum value held by the axis
    const long int _M_size; // The number of points along the axis/the axis's size
};

#endif
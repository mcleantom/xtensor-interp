#ifndef XTENSOR_INTERP_CONTAINER_H
#define XTENSOR_INTERP_CONTAINER_H

#include <cmath>
#include <cstdint>

template<typename T>
class Container {
public:
    typedef int64_t indexT;
    /**
     * @brief Returns True if the container is monotonic, else False.
     */
    virtual bool isMonotonic() const { return true; };
    /**
     * @brief Returns the minimum value held by the container
     */
    virtual T minValue() const = 0;
    /**
     * @brief Returns the maximum value held by the container
     */
    virtual T maxValue() const = 0;
    /**
     * @brief Returns the number of elements held by the container 
     */
    virtual indexT size() const = 0;
    /**
     * @brief Find the index in the grid for a given coordinate
     * 
     * @param coordinate The coordinate to find the index for
     * @param bounded If true, searching for a coordinate outside of the bounds of the axis will return -1.
     Else, it will return either the minimum or the maximum index when outside the bounds.
     * @return indexT The index of the value, or -1 if it is outside of the axis
     */
    virtual indexT findIndex(const T coordinate, const bool bounded) const = 0;
    /**
     * @brief Finds the coordinate value at the given index
     * 
     * @param index Index to find the coordinate value for, between 0 and size()-1
     * @return T The coordinate value
     */
    virtual T coordinateValue(const indexT index) const = 0;
    /**
     * @brief Returns True of the axis is arranged in ascending order
     */
    bool isAscending() const { return m_IsAscending; };
private:
    bool m_IsAscending{true};
};


template<typename T>
class Regular : public Container<T> {
public:
    using typename Container<T>::indexT;
    Regular(const T min, const T max, const indexT num)
    : m_Min(min)
    , m_Max(max)
    , m_Size(num)
    , m_Step((max-min)/(num-1))
    , m_InvStep(T(1.0)/m_Step) {};
    /// @copydoc Container::coordinate_value(const indexT) const
    T coordinateValue(const indexT index) const override {
        return m_Min + index * m_InvStep;
    };
    T minValue() const override { return m_Min; }
    T maxValue() const override { return m_Max; }
    indexT size() const override { return m_Size; }
    indexT findIndex(T coordinate, bool bounded) const override {
        indexT index = (coordinate - m_Min) * m_InvStep;

        if (index < 0) {
            return bounded ? -1 : 0;
        }
        
        if (index >= m_Size) {
            return bounded ? -1 : m_Size - 1;
        }

        return index;
    };
private:
    T m_Min;
    T m_Max;
    indexT m_Size;
    T m_Step;
    T m_InvStep; // The inverse step is stored to avoid division
};

#endif
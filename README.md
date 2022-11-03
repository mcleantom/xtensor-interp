# XTensor-Interp

The scipy regular grid interpolator does not scale well for high-dimensional data, as it is build to be resiliant to a lot of use cases (i.e. extrapolation).
This library uses XTensor to provide a RegularGridInterpolator-like class that has higher performance, with the caveat that it only interpolates for within the
bounds of the data, and that the data is on a true regular-spaced-grid (However, this requireent may be removed in the future). 
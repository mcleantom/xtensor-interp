# XTensor-Interp

XTensorInterp creates a class that allows the interpolation of N-Dimensional grids.

This class is designed to be similar to the Scipy RegularGridInterpolator, however it will scale better to higher-dimensional grids.

In addition, the library will allow for the interpolation for XArray Datasets, allowing for multiple datasets that are on identical grids to be efficiently interpolated.

## Development

Remember to initialize the repository by initializing the submodules using the command:

```
git clone --recurse-submodules https://github.com/mcleantom/xtensor-interp.git
```

### CMake

This project uses CMake to configure the project. You must have at least version 3.20.

### GTest

googletest is uses for unit testing the C++ library. 


## Similar Projects

This project is heavily influenced by [pangeo-pyinterp](https://github.com/CNES/pangeo-pyinterp).
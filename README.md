# XTensor-Interp

XTensorInterp implements a lazy-evaluation N-Dimensional interpolator for regular-gridded data using the library
xtensor.

You can set-up an interpolator class like:

```cpp
Regular<double> x_axis(0, 10, 20);
auto y_data = xt::linspace<double>(-5, 5, 20);
Interpolator<double> interp_1d(x_axis, y_data);
```

Then you can evaluate it by calling the class:
```cpp
auto x_in = xt::linspace<double>(0, 10, 100);
xt::xarray<double> res = interp_1d(x_in);
```

## Development

Remember to initialize the repository by initializing the submodules using the command:

```
git clone --recurse-submodules https://github.com/mcleantom/xtensor-interp.git
```

It is recommended to develop this library with VSCode. The recommended extensions to develop this library will be recommended when you open the project.

### CMake

This project uses CMake to configure the project and download it's dependencies. You must have at least version 3.20.

### GTest

googletest is uses for unit testing the C++ library (and is installed using CMake).

# Dimensions

A simple C++ template library for non-dimensionalisation. 

A templated class, ```Dimensions```, is defined that can be incorporated into a user-defined class by CRTP. Within the user-defined class methods to return a length-scale, density scale, and (optionally) time-scale must be defined. Via class inheritance, scales for various derived quantities are then made available. 
A simple example is as follows:

```c++
#include <iostream>
#include "Dimensions/Dimensions.hpp"

// Set up the dimensioned class, defining the necessary methods. 
class DimensionedClass : public Dimensions::Dimensions<DimensionedClass> {
public:  
  // Methods returning the required scales in SI units. 
  auto LengthScale() const { return 6.371e6; }
  auto DensityScale() const { return 5.514e3; }
  auto TimeScale() const { return 3600.0; }
};

int main(){
    // Form a class instance. 
    auto d = DimensionedClass();

    // print the corresponding acceleration scale, 
    std::cout << d.AccelerationScale() << std::endl;

    // Return the corresponding tractions scale, 
    std::cout << d.TractionScale() << std::endl;    
}
```

Optionally, the time-scale can be set to a default value 
```math
T = \frac{1}{\sqrt{\pi G \rho}}
```
where $G$ is the gravitational constant and $\rho$ the density scale. This is shown within the following example:
```c++
class DimensionedClass : public Dimensions::Dimensions<DimensionedClass, Dimensions::TimeScaleNotSet> {
public:  
  // Methods returning the required scales in SI units. 
  auto LengthScale() const { return 6.371e6; }
  auto DensityScale() const { return 5.514e3; }  
};

```


## Inclusion in another CMake project

The library is best included using CMake's  Fetch_Content method. The key additions to the including project's CMake file are:
```Cmake
include(FetchContent)
FetchContent_Declare(
  Dimensions
  GIT_REPOSITORY https://github.com/da380/Dimensions.git
  GIT_TAG main
)
FetchContent_MakeAvailable(Dimensions)
```
and then the dependency can be added to a given library or target in the usual manner. 

## Acknowledgements

The CMake files within this project are based on the examples provided in https://github.com/pr0g/cmake-examples.git

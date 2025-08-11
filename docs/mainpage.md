
\mainpage Dimensions: A C++20 Library for Dimensional Analysis

\section intro_sec Introduction

**Dimensions** is a modern, header-only C++20 library for performing dimensional analysis at compile time. It uses the Curiously Recurring Template Pattern (CRTP) to provide a type-safe and highly efficient framework for creating and using systems of physical units.

This library allows you to define a few fundamental scales (like length, mass, and time) and automatically derive the correct scaling factors for complex quantities like force, energy, and pressure.

<hr>

\section features_sec Key Features

- **Type-Safe:** All calculations are based on your defined scales, reducing the risk of unit-related errors.
- **Header-Only:** Simply include `Dimensions.hpp` to get started.
- **Compile-Time Performance:** `constexpr` is used extensively, allowing most scaling factors to be computed at compile time.
- **Flexible & Modern:** Built with C++20 and designed for easy integration using CMake's `FetchContent`.
- **Customizable Precision:** Easily select the floating-point type (`float`, `double`, etc.) for your calculations.

<hr>

\section quick_start_sec Quick Start

Using the library involves inheriting from one of the helper classes and defining your base scales.

\subsection step1_sec 1. Include the Header and Define Your System

Create a class that inherits from `Dimensions::MechanicalMassDimensions` and provide your base scales.

\code{.cpp}
#include "Dimensions.hpp"

// Define a system using CGS (Centimeter-Gram-Second) units
class CgsSystem
    : public Dimensions::MechanicalMassDimensions<CgsSystem, double> {
 public:
  // Define base scales relative to SI units (m, kg, s)
  constexpr auto LengthScale() const noexcept { return 0.01; }   // cm
  constexpr auto MassScale() const noexcept { return 0.001; }  // g
  constexpr auto TimeScale() const noexcept { return 1.0; }     // s
};
\endcode

\subsection step2_sec 2. Use the System

Instantiate your class and call its methods to get the desired scaling factors.

\code{.cpp}
#include <iostream>

int main() {
    CgsSystem cgs;

    // Get the scaling factor to convert Ergs (CGS energy) to Joules (SI energy)
    double erg_to_joule = cgs.EnergyScale();
    std::cout << "Energy Scale (Erg to Joule): " << erg_to_joule << std::endl;

    // Get the scaling factor to convert Dynes (CGS force) to Newtons (SI force)
    double dyne_to_newton = cgs.ForceScale();
    std::cout << "Force Scale (Dyne to Newton): " << dyne_to_newton << std::endl;
}
\endcode

<hr>

\section cmake_sec CMake Integration

This library is designed to be easily included in any modern CMake project using `FetchContent`.

\code{.cmake}
# In your project's CMakeLists.txt

include(FetchContent)

FetchContent_Declare(
    Dimensions
    GIT_REPOSITORY https://your-repo-url/Dimensions.git
    GIT_TAG        v0.1.0 # Or a specific commit
)
FetchContent_MakeAvailable(Dimensions)

# Now, link your target to Dimensions
add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE Dimensions)
\endcode


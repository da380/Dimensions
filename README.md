# Dimensions 📐

A modern, header-only C++20 library for type-safe dimensional analysis using compile-time calculations.

This library provides a framework to define physical unit systems. By specifying a few base scales (e.g., for length, mass, and time), it automatically derives the correct conversion factors for complex quantities like force, energy, and pressure.

---

## Key Features

-   **Header-Only**: Simply include `Dimensions.hpp` to get started.
-   **Modern C++**: Takes advantage of C++20 features like `constexpr` for maximum performance.
-   **Type-Safe**: Reduces the risk of unit-related errors by embedding scales into the type system.
-   **CMake Integration**: Designed to be effortlessly included in any project using `FetchContent`.
-   **Customizable Precision**: Choose the floating-point type (`float`, `double`, etc.) that fits your needs.

---

## How to Use in Your Project

The easiest way to integrate **Dimensions** is with CMake's `FetchContent`.

1.  **Add `FetchContent` to your `CMakeLists.txt`**:

    ```cmake
    include(FetchContent)

    FetchContent_Declare(
        Dimensions
        GIT_REPOSITORY https://your-repository-url/Dimensions.git
        GIT_TAG        v0.1.0 # Or a specific commit/branch
    )
    FetchContent_MakeAvailable(Dimensions)
    ```

2.  **Link your target to the library**:

    ```cmake
    add_executable(my_app main.cpp)

    # This automatically handles include paths and dependencies
    target_link_libraries(my_app PRIVATE Dimensions)
    ```

---

## License

This project is licensed under the BSD 3-Clause License

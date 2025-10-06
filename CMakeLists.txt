cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0135 NEW)

project(
    Dimensions
    VERSION 0.0.1
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependency Handling for NumericConcepts ---
# First, try to find an installed version of the package.
find_package(NumericConcepts QUIET)

# If it's not found, download it using FetchContent.
if(NOT NumericConcepts_FOUND)
    message(STATUS "NumericConcepts not found. Fetching from git...")
    include(FetchContent)
    FetchContent_Declare(
      NumericConcepts
      GIT_REPOSITORY https://github.com/da380/NumericConcepts.git
      GIT_TAG main
    )
    FetchContent_MakeAvailable(NumericConcepts)
    # Set a flag indicating we built this dependency ourselves
    set(FETCHED_NUMERIC_CONCEPTS TRUE)
else()
    message(STATUS "Found installed NumericConcepts version ${NumericConcepts_VERSION}")
endif()
# --- End of Dependency Handling ---

# Define a header-only INTERFACE library
add_library(${PROJECT_NAME} INTERFACE)

# Specify the include directory for this library
target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Link libraries to handle transitive dependencies correctly.
# This propagates the include directories from NumericConcepts to Dimensions.
if(NumericConcepts_FOUND)
    target_link_libraries(${PROJECT_NAME} INTERFACE NumericConcepts::NumericConcepts)
else()
    target_link_libraries(${PROJECT_NAME} INTERFACE NumericConcepts)
endif()


# --- Installation and Packaging ---
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Always install the main Dimensions target
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
)

# Also install the public header files
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Conditionally install the NumericConcepts target if it was fetched
if(FETCHED_NUMERIC_CONCEPTS)
    install(TARGETS NumericConcepts
        EXPORT ${PROJECT_NAME}Targets
    )
endif()

# Install the exported targets file
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake
)

# Generate the main config file from a template
configure_package_config_file(
    cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake
)
# Generate the package version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
# Install the generated config and version files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake
)
# --- End of Installation and Packaging ---


# --- Standalone Project Guard for examples and docs ---
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_subdirectory(examples)

    option(BUILD_DOCS "Build the Doxygen documentation" OFF)
    if(BUILD_DOCS)
      find_package(Doxygen REQUIRED)
      set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
      configure_file(Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
      add_custom_target(
          doc ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen..."
          VERBATIM
      )
    endif()


    # --- Optional GTest Integration ---
    option(BUILD_TESTS "Build the tests for Dimensions" OFF)

    if(BUILD_TESTS)
      enable_testing()
      include(FetchContent)

      # Prevent gtest from being installed alongside the library
      set(INSTALL_GTEST OFF)

      FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/v1.14.0.zip
      )
      FetchContent_MakeAvailable(googletest)

      add_subdirectory(tests)
  endif()
  # --- End of Optional GTest Integration ---


endif()


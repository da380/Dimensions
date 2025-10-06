# Create an executable for the tests
add_executable(run_tests
    test_dimensions.cpp
)

# Link the test executable against gtest and your library.
# Linking to Dimensions will transitively link to NumericConcepts.
target_link_libraries(run_tests PRIVATE
    GTest::gtest_main
    Dimensions
)

# Automatically discover and add tests to CTest
include(GoogleTest)
gtest_discover_tests(run_tests)

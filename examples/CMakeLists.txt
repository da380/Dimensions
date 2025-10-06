add_executable(ex1 ex1.cpp)
target_link_libraries(ex1 Dimensions)


# --- Add this block for debugging ---
get_target_property(EX1_INCLUDES ex1 INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "DEBUG: ex1 include directories: ${EX1_INCLUDES}")
# --- End of debug block ---
# ============ include google/gtest ============
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        release-1.11.0
# )
# FetchContent_MakeAvailable(googletest)
# add_library(GTest::GTest INTERFACE IMPORTED)
# target_link_libraries(GTest::GTest INTERFACE gtest_main)
# ==============================================

# EXAMPLE TEST
#
# 1. create the test executable
# add_executable(test_executable_name <test sources...>)
#
# 2. link the gtest and ere libraries and other libraries
# target_link_libraries(test_executable_name PRIVATE GTest::GTest ere <other libraries...>)
#
# 3. add the test to the ctest suite
# add_test(NAME gtest_name COMMAND test WORKING_DIRECTORY ${CMAKE_BINARY_DIR})



# ================== test general ==================
add_executable(general general.cpp)
target_link_libraries(general PRIVATE ere)
add_test(NAME test_general COMMAND general WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
# ==================================================

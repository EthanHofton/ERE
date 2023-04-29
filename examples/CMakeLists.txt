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

# ================== include assimp ================
include(FetchContent)
FetchContent_Declare(
  assimp
  GIT_REPOSITORY https://github.com/assimp/assimp.git
)
FetchContent_MakeAvailable(assimp)
# ==================================================

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


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# ================== test skybox ==================
add_executable(skybox skybox.cpp)
target_link_libraries(skybox PRIVATE ere assimp)
# ==================================================

# ================== test intanced rendering ==================
add_executable(instanced_rendering instanced_rendering.cpp)
target_link_libraries(instanced_rendering PRIVATE ere)
# ==================================================

# ================== test lighting ==================
add_executable(lighting lighting.cpp)
target_link_libraries(lighting PRIVATE ere)
# ==================================================

# ================== test model lighting ==================
add_executable(model_loading model_loading.cpp)
target_link_libraries(model_loading PRIVATE ere assimp)
# ==================================================

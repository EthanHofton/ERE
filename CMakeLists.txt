cmake_minimum_required(VERSION 3.25.1)
include(CMakeDependentOption)

# project name and version number
project(ere VERSION 0.1.0)

# set cxx standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# get all sourcers
file(GLOB SOURCES "src/*.cpp")

# store the input and output config files
set(CONFIG_IN ${CMAKE_CURRENT_SOURCE_DIR}/ereConfig.hpp.in)
set(CONFIG_OUT ${CMAKE_CURRENT_BINARY_DIR}/ereConfig.hpp)

# build docs option
option(BUILD_DOCS "Build documentation" OFF)

# check if build docs is selected
if (BUILD_DOCS)
    # find doxygen package
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        # set input and output files 
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("-- Doxygen build started")

        # add doxygen docs target
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else(DOXYGEN_FOUND)
        # show warning message if doxygen not found
        message("-- Doxygen need to be installed to generate the doxygen documentation")
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)

# add util subdirectory
add_subdirectory(lib/util)

# add glm
add_subdirectory(lib/glm)


# -- WINDOWING API -- #
# if not use GLFW, use platform specific API
option(USE_GLFW "Use GLFW as the windowing libary" ON)
cmake_dependent_option(USE_COCOA "Use COCOA as the windowing libary" ON "APPLE; NOT USE_GLFW" OFF)
cmake_dependent_option(USE_WIN32 "Use WIN32 as the windowing libary" ON "WIN32; NOT USE_GLFW" OFF)

if (USE_GLFW)
    message("-- using GLFW as windowing API")
    add_subdirectory(lib/glfw)
    list(APPEND EXTRA_LIBS glfw)
endif(USE_GLFW)

if (USE_COCOA)
    message("-- using COCOA as windowing API")
endif(USE_COCOA)

if (USE_WIN32)
    message("-- using WIN32 as windowing API")
endif(USE_WIN32)

# -- Graphics API -- #
# if not use opengl, use platform specific API
option(USE_OPENGL "Use OpenGL as the graphics API" ON)
cmake_dependent_option(USE_METAL "Use METAL as the graphics API" ON "APPLE; NOT USE_OPENGL" OFF)
cmake_dependent_option(USE_VULKAN "Use WIN32 as the graphics API" ON "WIN32; NOT USE_OPENGL" OFF)

# setup OpenGL and glad
if (USE_OPENGL)
    find_package(OpenGL REQUIRED)
    list(APPEND EXTRA_LIBS ${OPENGL_LIBRARIES})

    # also include GLAD
    add_subdirectory(lib/glad)
    # create glad target
    glad_add_library(glad_gl_core_33 STATIC API gl:core=3.3)
    list(APPEND EXTRA_LIBS glad_gl_core_33)
endif(USE_OPENGL)

configure_file(${CONFIG_IN} ${CONFIG_OUT})

# add library target
add_library(ere ${SOURCES})

# add include directory
target_include_directories(ere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(ere PUBLIC ${PROJECT_BINARY_DIR})

# link to libaries
target_link_libraries(ere PUBLIC util)
target_link_libraries(ere PUBLIC glm)
target_link_libraries(ere PRIVATE ${EXTRA_LIBS})

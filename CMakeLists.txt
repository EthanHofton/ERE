cmake_minimum_required(VERSION 3.25.1)

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

# add library target
add_library(ere ${SOURCES})

# add include directory
target_include_directories(ere PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(ere PUBLIC ${PROJECT_BINARY_DIR})

target_link_libraries(ere PUBLIC util)

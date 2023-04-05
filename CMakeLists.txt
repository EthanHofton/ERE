cmake_minimum_required(VERSION 3.26.0)

# CMake useful variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

project(ere VERSION 1.0.0 LANGUAGES CXX)

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Mac needed variables (adapt according to your needs)
set(CMAKE_MACOSX_RPATH ON)
#set(CMAKE_SKIP_BUILD_RPATH FALSE)
#set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
#set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

enable_testing()

add_subdirectory(src)
# include include directory AFTER src so that the library can use the configure file
add_subdirectory(include)
# include test directroy AFTER src so that the test can use the library built
add_subdirectory(test)

# docs
option(BUILD_DOCS "Build documentation" OFF)
if(BUILD_DOCS)
    # find doxygen and generate documentation
    find_package(Doxygen)
    # check doxygen was found
    if (DOXYGEN_FOUND)
        # use the readme as main page
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
        # use doxygen_add_docs to generate documentation
        doxygen_add_docs(
            ere_docs
            ${CMAKE_SOURCE_DIR}
            COMMENT "Generate man pages"
        )
    else()
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
endif()

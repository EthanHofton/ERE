## ERE

***E***thans ***R***ender ***Engine***

Cross-platform render engine.

## Build Instructions

### Using CMake:

#### Build static library:

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=[Release|Debug|RelWithDebInfo]
cmake --build .
```

This will create all the required libraries in `lib/`.

#### CMake Include

Inside your `CMakeLists.txt`:

```cmake
include(FetchContent)
FetchContent_Declare(
  ere
  GIT_REPOSITORY https://github.com/EthanHofton/ere.git
  GIT_TAG main
)
FetchContent_MakeAvailable(ere)

...

add_executable(${EXE_NAME} ${EXE_SRC})
target_link_libraries(${EXE_NAME} PUBLIC ere)
```

#### Build Examples

```
mkdir build
cd build
cmake .. -DBUILD_EXAMPLES=ON
cmake --build .
```

#### Build Docs

```
mkdir build
cd build
cmake .. -BUILD_DOCS=ON
cmake --build . --target ere_docs
```

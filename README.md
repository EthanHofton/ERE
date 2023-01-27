# ERE

### **_E_**thans **_R_**ender **_E_**ngine

# Compilation

To compile:

```
mkdir build
cd build
cmake ../
cmake --build .
```

This will create `libere.a` inside the build directory. If `-DBUILD_DOCS` is used, docs will be created in `build/docs`

# cmake usage

add to your CMakeLists.txt

```
add_subdirectory(path/to/ere)

...

target_link_libaries(targetName ere)
```

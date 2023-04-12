include(FetchContent)

# ======= include EthanHofton/util =======
message("-- fetching EthanHofton/util")
FetchContent_Declare(
  util
  GIT_REPOSITORY https://github.com/EthanHofton/util.git
)
FetchContent_MakeAvailable(util)
# ========================================

# ======= include g-truc/glm =======
message("-- fetching g-truc/glm")
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
)
FetchContent_MakeAvailable(glm)
# ========================================

# ======= include imgui/imgui ============
message("-- fetching imgui/imgui")
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/EthanHofton/imgui.git
  GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)
# ========================================

# ======= include glfw/glfw =======
option(USE_GLFW "Use GLFW" ON)
if (USE_GLFW)
    message("-- fetching glfw/glfw")
    FetchContent_Declare(
      glfw
      GIT_REPOSITORY https://github.com/glfw/glfw
    )
    FetchContent_MakeAvailable(glfw)
    list(APPEND EXTRA_LIBS glfw)
endif()
# ========================================

# ======= openGL =======
if (USE_OPENGL)
    find_package(OpenGL REQUIRED)
    list(APPEND EXTRA_LIBS OpenGL::GL)
    list(APPEND EXTRA_LIBS glad)
endif()
# ======================



# ======= SOURCES =======
set(SOURCES
    opengl_framebuffer.cpp
    camera_3d.cpp
    render_api.cpp
    opengl_texture.cpp
    opengl_vertex_array.cpp
    opengl_index_buffer.cpp
    opengl_vertex_buffer.cpp
    opengl_shader.cpp
    opengl_renderer.cpp
    imgui_impl_opengl3.cpp
    imgui_layer.cpp
    glfw_window.cpp
    layer.cpp
    entry_point.cpp
    application.cpp)
# =======================





# ======= LIBRARY =======
set(LIBARY_NAME "ere")

add_library(${LIBARY_NAME} ${SOURCES})

set_target_properties(${LIBARY_NAME} PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  VERSION ${VERSION}
)
# =======================





# ======= INCLUDES =======
target_include_directories(${LIBARY_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
)
# ========================





# ======= LINKS =======
target_link_libraries(${LIBARY_NAME} PUBLIC
    util
    glm
    imgui
)
target_link_libraries(${LIBARY_NAME} PRIVATE 
    ${EXTRA_LIBS}
    stb_image
)
# ======================




# ======= INSTALL =======
install(TARGETS ${LIBRARY_NAME}
  EXPORT ${PROJECT_NAME}Targets            # for downstream dependencies
  ARCHIVE DESTINATION lib COMPONENT libs   # static lib
  RUNTIME DESTINATION bin COMPONENT libs   # binaries
  LIBRARY DESTINATION lib COMPONENT libs   # shared lib
  FRAMEWORK DESTINATION bin COMPONENT libs # for mac
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME} COMPONENT devel   # headers for mac (note the different component -> different package)
  INCLUDES DESTINATION include             # headers
)
# =======================

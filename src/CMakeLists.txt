# ======= include EthanHofton/util =======
include(FetchContent)

FetchContent_Declare(
  util
  GIT_REPOSITORY https://github.com/EthanHofton/util.git
)
FetchContent_MakeAvailable(util)
# ========================================

# ======= include g-truc/glm =======
include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
)
FetchContent_MakeAvailable(glm)
# ========================================

# ======= include glfw/glfw =======
option(USE_GLFW "Use GLFW" ON)

if (USE_GLFW)
    FetchContent_Declare(
      glfw
      GIT_REPOSITORY https://github.com/glfw/glfw
    )
    FetchContent_MakeAvailable(glfw)
    list(APPEND EXTRA_LIBS glfw)
endif()



# ======= SOURCES =======
set(SOURCES
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
)
target_link_libraries(${LIBARY_NAME} PRIVATE ${EXTRA_LIBS})
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

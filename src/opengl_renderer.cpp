#include <ere/impl/opengl/opengl_renderer.hpp>
#include <ere/core/logger.hpp>

#ifdef USE_OPENGL

#ifdef USE_GLFW
#include <GLFW/glfw3.h>
#endif

namespace ere {

ref<render_api> render_api::get_renderer() {
    static ref<opengl_renderer> s_renderer = createRef<opengl_renderer>();
    return s_renderer;
}

void opengl_renderer::init_impl() {
    // * initalize glad
    if (!gladLoadGL()) {
        ERE_ERROR("Failed to initialize glad!");
        throw std::runtime_error("Failed to initialize glad!");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
}

void opengl_renderer::set_viewport_impl(const glm::vec2& t_size) {
    glViewport(0, 0, t_size.x, t_size.y);
}

void opengl_renderer::clear_color_impl(const glm::vec4& t_color) {
    glClearColor(t_color.r, t_color.g, t_color.b, t_color.a);
}

void opengl_renderer::clear_buffer_impl() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void opengl_renderer::pre_window_setup_impl() {
#ifdef USE_GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
}

}

#endif

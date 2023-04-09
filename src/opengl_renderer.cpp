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

void opengl_renderer::enable_wireframe_impl() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void opengl_renderer::disable_wireframe_impl() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void opengl_renderer::pre_window_setup_impl() {
#ifdef USE_GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
}

void opengl_renderer::draw_indexed_impl(const ref<vertex_array_api>& t_vao) {
    // simple error checking
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        // ERE_ERROR("OpenGL error: {}", err);
    }

    if (!t_vao->get_index_buffer()) {
        ERE_ERROR("No index buffer defined!");
    } else {
        t_vao->bind();
        glDrawElements(GL_TRIANGLES, t_vao->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr);
        t_vao->unbind();
    }
}

void opengl_renderer::draw_arrays_impl(const ref<vertex_array_api>& t_vao, int t_vertex_count) {
    t_vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, t_vertex_count);
    t_vao->unbind();
}

}

#endif

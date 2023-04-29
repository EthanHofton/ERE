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

    enable_blending();
    set_blending_function(blending_function::SRC_ALPHA, blending_function::ONE_MINUS_SRC_ALPHA);

    enable_depth_testing();

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_MULTISAMPLE);
}

void opengl_renderer::set_viewport_impl(const glm::vec2& t_size) {
    static glm::vec2 s_viewport_size = glm::vec2(0.0f);

    if (s_viewport_size == t_size) {
        return;
    }

    glViewport(0, 0, t_size.x, t_size.y);

    s_viewport_size = t_size;
}

glm::vec2 opengl_renderer::get_viewport_impl() const {
    glm::ivec4 viewport;
    glGetIntegerv(GL_VIEWPORT, &viewport[0]);

    return glm::vec2(viewport.z, viewport.w);
}

void opengl_renderer::clear_color_impl(const glm::vec4& t_color) {
    glClearColor(t_color.r, t_color.g, t_color.b, t_color.a);
}

void opengl_renderer::clear_buffers_impl() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void opengl_renderer::clear_color_buffer_impl() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void opengl_renderer::clear_depth_buffer_impl() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void opengl_renderer::clear_stencil_buffer_impl() {
    glClear(GL_STENCIL_BUFFER_BIT);
}

void opengl_renderer::enable_wireframe_impl() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void opengl_renderer::disable_wireframe_impl() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void opengl_renderer::enable_depth_testing_impl() {
    glEnable(GL_DEPTH_TEST);
}

void opengl_renderer::enable_depth_test_write_impl() {
    glDepthMask(GL_TRUE);
}

void opengl_renderer::disable_depth_testing_impl() {
    glDisable(GL_DEPTH_TEST);
}

void opengl_renderer::disable_depth_test_write_impl() {
    glDepthMask(GL_FALSE);
}

void opengl_renderer::set_depth_testing_function_impl(const render_api::testing_function &t_function) {
    glDepthFunc(get_gl_testing_function(t_function));
}

void opengl_renderer::enable_blending_impl() {
    glEnable(GL_BLEND);
}

void opengl_renderer::disable_blending_impl() {
    glDisable(GL_BLEND);
}

void opengl_renderer::set_blending_function_impl(const render_api::blending_function &t_source, const render_api::blending_function &t_destination) {
    glBlendFunc(get_gl_blending_function(t_source), get_gl_blending_function(t_destination));
}

void opengl_renderer::enable_stencil_testing_impl() {
    glEnable(GL_STENCIL_TEST);
}

void opengl_renderer::disable_stencil_testing_impl() {
    glDisable(GL_STENCIL_TEST);
}

void opengl_renderer::set_stencil_mask_impl(unsigned char t_mask) {
    glStencilMask(t_mask);
}

void opengl_renderer::set_stencil_function_impl(const render_api::testing_function &t_function, int t_reference, unsigned char t_mask) {
    glStencilFunc(get_gl_testing_function(t_function), t_reference, t_mask);
}

void opengl_renderer::set_stencil_operation_impl(const render_api::stencil_operation &t_fail, const render_api::stencil_operation &t_pass_depth_fail, const render_api::stencil_operation &t_pass_depth_pass) {
    glStencilOp(get_gl_stencil_operation(t_fail), get_gl_stencil_operation(t_pass_depth_fail), get_gl_stencil_operation(t_pass_depth_pass));
}


void opengl_renderer::enable_culling_impl(const render_api::culling_face& t_face, const render_api::culling_direction& t_direction) {
    glEnable(GL_CULL_FACE);
    glCullFace(get_gl_culling_face(t_face));
    glFrontFace(get_gl_culling_direction(t_direction));
}

void opengl_renderer::disable_culling_impl() {
    glDisable(GL_CULL_FACE);
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
        ERE_ERROR("OpenGL error: {}", err);
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
    // simple error checking
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        ERE_ERROR("OpenGL error: {}", err);
    }

    t_vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, t_vertex_count);
    t_vao->unbind();
}

void opengl_renderer::draw_indexed_instanced_impl(const ref<vertex_array_api> &t_vao, int t_instance_count) {
    // simple error checking
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        ERE_ERROR("OpenGL error: {}", err);
    }

    if (!t_vao->get_index_buffer()) {
        ERE_ERROR("No index buffer defined!");
    } else {
        t_vao->bind();
        glDrawElementsInstanced(GL_TRIANGLES, t_vao->get_index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr, t_instance_count);
        t_vao->unbind();
    }
}

void opengl_renderer::draw_arrays_instanced_impl(const ref<vertex_array_api> &t_vao, int t_vertex_count, int t_instance_count) {
    // simple error checking
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR) {
        ERE_ERROR("OpenGL error: {}", err);
    }

    t_vao->bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, t_vertex_count, t_instance_count);
    t_vao->unbind();
}


}

#endif

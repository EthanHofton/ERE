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
    enable_depth_testing();

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_MULTISAMPLE);
}

void opengl_renderer::set_viewport_impl(const glm::vec2& t_size) {
    glViewport(0, 0, t_size.x, t_size.y);
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
    t_vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, t_vertex_count);
    t_vao->unbind();
}

GLenum opengl_renderer::get_gl_culling_face(render_api::culling_face t_face) {
    switch (t_face) {
        case render_api::culling_face::FRONT:
            return GL_FRONT;
        case render_api::culling_face::BACK:
            return GL_BACK;
        case render_api::culling_face::FRONT_AND_BACK:
            return GL_FRONT_AND_BACK;
    }
}

GLenum opengl_renderer::get_gl_culling_direction(render_api::culling_direction t_direction) {
    switch (t_direction) {
        case render_api::culling_direction::CLOCKWISE:
            return GL_CW;
        case render_api::culling_direction::COUNTER_CLOCKWISE:
            return GL_CCW;
    }
}

GLenum opengl_renderer::get_gl_testing_function(render_api::testing_function t_function) {
    switch (t_function) {
        case render_api::testing_function::NEVER:
            return GL_NEVER;
        case render_api::testing_function::LESS:
            return GL_LESS;
        case render_api::testing_function::EQUAL:
            return GL_EQUAL;
        case render_api::testing_function::LEQUAL:
            return GL_LEQUAL;
        case render_api::testing_function::GREATER:
            return GL_GREATER;
        case render_api::testing_function::NOTEQUAL:
            return GL_NOTEQUAL;
        case render_api::testing_function::GEQUAL:
            return GL_GEQUAL;
        case render_api::testing_function::ALWAYS:
            return GL_ALWAYS;
    }
}

GLenum opengl_renderer::get_gl_blending_function(render_api::blending_function t_function) {
    switch (t_function) {
        case render_api::blending_function::ZERO:
            return GL_ZERO;
        case render_api::blending_function::ONE:
            return GL_ONE;
        case render_api::blending_function::SRC_COLOR:
            return GL_SRC_COLOR;
        case render_api::blending_function::ONE_MINUS_SRC_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
        case render_api::blending_function::DST_COLOR:
            return GL_DST_COLOR;
        case render_api::blending_function::ONE_MINUS_DST_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
        case render_api::blending_function::SRC_ALPHA:
            return GL_SRC_ALPHA;
        case render_api::blending_function::ONE_MINUS_SRC_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
        case render_api::blending_function::DST_ALPHA:
            return GL_DST_ALPHA;
        case render_api::blending_function::ONE_MINUS_DST_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
        case render_api::blending_function::CONSTANT_COLOR:
            return GL_CONSTANT_COLOR;
        case render_api::blending_function::ONE_MINUS_CONSTANT_COLOR:
            return GL_ONE_MINUS_CONSTANT_COLOR;
        case render_api::blending_function::CONSTANT_ALPHA:
            return GL_CONSTANT_ALPHA;
        case render_api::blending_function::ONE_MINUS_CONSTANT_ALPHA:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
    }
}

GLenum opengl_renderer::get_gl_stencil_operation(render_api::stencil_operation t_operation) {
    switch (t_operation) {
        case render_api::stencil_operation::KEEP:
            return GL_KEEP;
        case render_api::stencil_operation::ZERO:
            return GL_ZERO;
        case render_api::stencil_operation::REPLACE:
            return GL_REPLACE;
        case render_api::stencil_operation::INCR:
            return GL_INCR;
        case render_api::stencil_operation::INCR_WRAP:
            return GL_INCR_WRAP;
        case render_api::stencil_operation::DECR:
            return GL_DECR;
        case render_api::stencil_operation::DECR_WRAP:
            return GL_DECR_WRAP;
        case render_api::stencil_operation::INVERT:
            return GL_INVERT;
    }
}

}

#endif

#include <ere/impl/opengl/opengl_vertex_array.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

static GLenum ere_shader_type_to_gl(const buffer_layout::shader_type& t_type) {
    switch (t_type) {
        case buffer_layout::shader_type::float_1: return GL_FLOAT;
        case buffer_layout::shader_type::float_2: return GL_FLOAT;
        case buffer_layout::shader_type::float_3: return GL_FLOAT;
        case buffer_layout::shader_type::float_4: return GL_FLOAT;
        case buffer_layout::shader_type::int_1: return GL_INT;
        case buffer_layout::shader_type::int_2: return GL_INT;
        case buffer_layout::shader_type::int_3: return GL_INT;
        case buffer_layout::shader_type::int_4: return GL_INT;
        case buffer_layout::shader_type::bool_1: return GL_BOOL;
        case buffer_layout::shader_type::matf_3: return GL_FLOAT;
        case buffer_layout::shader_type::matf_4: return GL_FLOAT;
        default: return 0;
    }
}

ref<vertex_array_api> vertex_array_api::create_vertex_array_api() {
    return std::make_shared<opengl_vertex_array>();
}

opengl_vertex_array::opengl_vertex_array() {
    glGenVertexArrays(1, &m_VAO);
}

opengl_vertex_array::~opengl_vertex_array() {
    glDeleteVertexArrays(1, &m_VAO);
}

void opengl_vertex_array::bind() const {
    glBindVertexArray(m_VAO);
}

void opengl_vertex_array::unbind() const {
    glBindVertexArray(0);
}

void opengl_vertex_array::add_vertex_buffer(const ref<vertex_buffer_api>& t_vbo) {
    bind();
    t_vbo->bind();
    int index = 0;
    const auto& layout = t_vbo->get_layout();
    for (const auto& element : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.count,
                              ere_shader_type_to_gl(element.type),
                              element.normalized,
                              layout.get_stride(),
                              (const void*)element.offset);
        index++;
    }
    m_vbos.push_back(t_vbo);
}

void opengl_vertex_array::set_index_buffer(const ref<index_buffer_api>& t_ibo) {
    bind();
    t_ibo->bind();
    m_ibo = t_ibo;
}

}

#endif

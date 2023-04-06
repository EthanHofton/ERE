#include <ere/impl/opengl/opengl_vertex_buffer.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

ref<vertex_buffer_api> vertex_buffer_api::create_vertex_buffer_api(uint32_t t_size) {
    return std::make_shared<opengl_vertex_buffer>(t_size);
}

ref<vertex_buffer_api> vertex_buffer_api::create_vertex_buffer_api(const void* t_data, uint32_t t_size) {
    return std::make_shared<opengl_vertex_buffer>(t_data, t_size);
}

opengl_vertex_buffer::opengl_vertex_buffer(uint32_t t_size) {
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, t_size, nullptr, GL_DYNAMIC_DRAW);
}

opengl_vertex_buffer::opengl_vertex_buffer(const void* t_data, uint32_t t_size) {
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, t_size, t_data, GL_STATIC_DRAW);
}

opengl_vertex_buffer::~opengl_vertex_buffer() {
    glDeleteBuffers(1, &m_VBO);
}

void opengl_vertex_buffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void opengl_vertex_buffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void opengl_vertex_buffer::set_data(const void* t_data, uint32_t t_size) {
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, t_size, t_data);
}

}

#endif

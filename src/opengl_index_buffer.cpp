#include <ere/impl/opengl/opengl_index_buffer.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

ref<index_buffer_api> index_buffer_api::create_index_buffer_api(uint32_t t_size) {
    return std::make_shared<opengl_index_buffer>(t_size);
}

ref<index_buffer_api> index_buffer_api::create_index_buffer_api(uint32_t* t_data, uint32_t t_size) {
    return std::make_shared<opengl_index_buffer>(t_data, t_size);
}

opengl_index_buffer::opengl_index_buffer(uint32_t t_size) {
    // IBO not valid until VAO is bound
    // create as array buffer instead
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ARRAY_BUFFER, t_size, nullptr, GL_DYNAMIC_DRAW);
}

opengl_index_buffer::opengl_index_buffer(uint32_t* t_data, uint32_t t_size) {
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ARRAY_BUFFER, t_size, t_data, GL_STATIC_DRAW);
    m_count = t_size / sizeof(uint32_t);
}

opengl_index_buffer::~opengl_index_buffer() {
    glDeleteBuffers(1, &m_IBO);
}

void opengl_index_buffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
}

void opengl_index_buffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void opengl_index_buffer::set_data(const uint32_t* t_data, uint32_t t_size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, t_size, t_data);
    m_count = t_size / sizeof(uint32_t);
}

}

#endif

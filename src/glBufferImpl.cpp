#include <ere/impl/opengl/glBufferImpl.hpp>

#ifdef USE_OPENGL
#include <glad/gl.h>

namespace ere {

/* -- VERTEX BUFFER -- */

ref<vertexBufferAPI> vertexBufferAPI::make(const uint32_t &t_size) {
    return createRef<glVertexBuffer>(t_size);
}

ref<vertexBufferAPI> vertexBufferAPI::make(void *t_vertices, const uint32_t &t_size) {
    return createRef<glVertexBuffer>(t_vertices, t_size);
}

glVertexBuffer::glVertexBuffer(const uint32_t& t_size) {
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, t_size, nullptr, GL_DYNAMIC_DRAW);
}

glVertexBuffer::glVertexBuffer(void* t_vertices, const uint32_t& t_size) {
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, t_size, t_vertices, GL_STATIC_DRAW);
}

glVertexBuffer::~glVertexBuffer() {
    glDeleteBuffers(1, &m_VBO);
}

void glVertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
} 

void glVertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void glVertexBuffer::setData(const void* t_data, uint32_t t_size) {
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, t_size, t_data);
}

/* -- INDEX BUFFER -- */

ref<indexBufferAPI> indexBufferAPI::make(const uint32_t &t_size) {
    return createRef<glIndexBuffer>(t_size);
}

ref<indexBufferAPI> indexBufferAPI::make(uint32_t *t_indices, const uint32_t &t_size) {
    return createRef<glIndexBuffer>(t_indices, t_size);
}

glIndexBuffer::glIndexBuffer(const uint32_t& t_count) : m_count(t_count) {
    glCreateBuffers(1, &m_IBO);

    // * IBO not valid without an activly bound VAO
    // * bind with GL_ARRAY_BUFFER to load data regadreless of state
    glBindBuffer(GL_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * m_count, nullptr, GL_DYNAMIC_DRAW);
}

glIndexBuffer::glIndexBuffer(uint32_t* t_indices, const uint32_t& t_count) : m_count(t_count) {
    glCreateBuffers(1, &m_IBO);

    // * IBO not valid without an activly bound VAO
    // * bind with GL_ARRAY_BUFFER to load data regadreless of state
    glBindBuffer(GL_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uint32_t) * m_count, t_indices, GL_DYNAMIC_DRAW);
}

glIndexBuffer::~glIndexBuffer() {
    glDeleteBuffers(1, &m_IBO);
}

void glIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
}

void glIndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t glIndexBuffer::getCount() const {
    return m_count;
}

void glIndexBuffer::setData(uint32_t* t_data, uint32_t t_count) {
    m_count = t_count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_count * sizeof(uint32_t), t_data);
}

}

#endif

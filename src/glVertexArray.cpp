#include <ere/impl/opengl/glVertexArray.hpp>

#ifdef USE_OPENGL
#include <glad/gl.h>

namespace ere {

static GLenum shaderDataTypeToOpenGLBaseType(shaderDataType type) {
    switch (type) {
        case shaderDataType::Bool:   return GL_BOOL;
        case shaderDataType::Int:    return GL_INT;
        case shaderDataType::UInt:   return GL_UNSIGNED_INT;
        case shaderDataType::Float:  return GL_FLOAT;
        case shaderDataType::Double: return GL_DOUBLE;
        case shaderDataType::BVec2:  return GL_BOOL;
        case shaderDataType::BVec3:  return GL_BOOL;
        case shaderDataType::BVec4:  return GL_BOOL;
        case shaderDataType::IVec2:  return GL_INT;
        case shaderDataType::IVec3:  return GL_INT;
        case shaderDataType::IVec4:  return GL_INT;
        case shaderDataType::UVec2:  return GL_UNSIGNED_INT;
        case shaderDataType::UVec3:  return GL_UNSIGNED_INT;
        case shaderDataType::UVec4:  return GL_UNSIGNED_INT;
        case shaderDataType::Vec2:   return GL_FLOAT;
        case shaderDataType::Vec3:   return GL_FLOAT;
        case shaderDataType::Vec4:   return GL_FLOAT;
        case shaderDataType::DVec2:  return GL_DOUBLE;
        case shaderDataType::DVec3:  return GL_DOUBLE;
        case shaderDataType::DVec4:  return GL_DOUBLE;
    }

    return 0;
}

ref<vertexArrayAPI> vertexArrayAPI::make() {
    return createRef<glVertexArray>();
}

glVertexArray::glVertexArray() {
    glCreateVertexArrays(1, &m_VAO);
}

glVertexArray::~glVertexArray() {
    glDeleteVertexArrays(1, &m_VAO);
}

void glVertexArray::bind() const {
    glBindVertexArray(m_VAO);
}

void glVertexArray::unbind() const {
    glBindVertexArray(0);
} 

void glVertexArray::addVertexBuffer(const ref<vertexBufferAPI>& t_vertexBuffer) {
    glBindVertexArray(m_VAO);
    t_vertexBuffer->bind();

    const auto& layout = t_vertexBuffer->getLayout();
    for (const auto& elem : layout) {
        glEnableVertexAttribArray(m_vertexBufferIndex);
        glVertexAttribPointer(m_vertexBufferIndex,
                              elem.getComponentCount(),
                              shaderDataTypeToOpenGLBaseType(elem.m_type),
                              elem.m_normalized ? GL_TRUE : GL_FALSE,
                              layout.getStride(),
                              (const void*)elem.m_offset);
        m_vertexBufferIndex++;
    }

    m_vertexBuffers.push_back(t_vertexBuffer);
}

void glVertexArray::addIndexBuffer(const ref<indexBufferAPI>& t_indexBuffer) {
    glBindVertexArray(m_VAO);
    t_indexBuffer->bind();
    m_indexBuffer = t_indexBuffer;
}

}

#endif

#ifndef ERE_IMPL_OPENGL_GL_VERTEX_ARRAY_HPP
#define ERE_IMPL_OPENGL_GL_VERTEX_ARRAY_HPP


#include <ereConfig.hpp>
#ifdef USE_OPENGL

#include <ere/api/vertexArrayAPI.hpp>

namespace ere {

class glVertexArray : public vertexArrayAPI {
public:

    glVertexArray();
    virtual ~glVertexArray();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void addVertexBuffer(const ref<vertexBufferAPI>& t_vertexBuffer) override;
    virtual void addIndexBuffer(const ref<indexBufferAPI>& t_indexBuffer) override; 

    inline virtual const std::vector<ref<vertexBufferAPI>>& getVertexBuffers() const override { return m_vertexBuffers; }
    inline virtual const ref<indexBufferAPI>& getIndexBuffer() const override { return m_indexBuffer; }

private:

    uint32_t m_VAO;
    uint32_t m_vertexBufferIndex;
    std::vector<ref<vertexBufferAPI>> m_vertexBuffers;
    ref<indexBufferAPI> m_indexBuffer;
};

}

#endif

#endif

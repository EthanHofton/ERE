#ifndef ERE_IMPL_OPENGL_GL_BUFFER_IMPL_HPP
#define ERE_IMPL_OPENGL_GL_BUFFER_IMPL_HPP

#include <ereConfig.hpp>
#ifdef USE_OPENGL

#include <ere/api/bufferAPI.hpp>

namespace ere {

class glVertexBuffer : public vertexBufferAPI {

    glVertexBuffer(const uint32_t& t_size);
    glVertexBuffer(void* t_vertices, const uint32_t& t_size);
    virtual ~glVertexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void setData(const void* t_data, uint32_t t_size) override;
    inline virtual const bufferLayout& getLayout() const override { return m_layout; }
    inline virtual void setLayout(const bufferLayout& t_layout) override { m_layout = t_layout; }

private:

    unsigned int m_VBO;
    bufferLayout m_layout;
};

class glIndexBuffer : public indexBufferAPI {

    glIndexBuffer(const uint32_t& t_count);
    glIndexBuffer(uint32_t* t_indices, const uint32_t& t_count);
    virtual ~glIndexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void setData(uint32_t* t_data, uint32_t t_count) override;

private:

    unsigned int m_IBO;
    uint32_t m_count;
};

}

#endif

#endif

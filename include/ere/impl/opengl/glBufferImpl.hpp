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
    virtual const bufferLayout& getLayout() const override;
    virtual void setLayout(const bufferLayout& t_layout) override;

private:

    unsigned int m_VBO;
    bufferLayout m_layout;
};

class glIndexBuffer : public indexBufferAPI {

    virtual ~glIndexBuffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void setData(uint32_t* t_data, uint32_t t_size) override;

private:

    unsigned int m_IBO;
};

}

#endif

#endif

#ifndef __ERE_OPENGL_VERTEX_BUFFER_HPP__
#define __ERE_OPENGL_VERTEX_BUFFER_HPP__

#include <ere/ere_config.hpp>

#ifdef USE_OPENGL

#include <ere/api/vertex_buffer_api.hpp>

namespace ere {

class opengl_vertex_buffer : public vertex_buffer_api {
public:

    opengl_vertex_buffer(uint32_t t_size);
    opengl_vertex_buffer(void* t_data, uint32_t t_size);
    virtual ~opengl_vertex_buffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void set_data(const void* t_data, uint32_t t_size) override;

private:

    unsigned int m_VBO;
};

}

#endif // USE_OPENGL

#endif // __ERE_OPENGL_VERTEX_BUFFER_HPP__

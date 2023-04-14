#ifndef __ERE_OPENGL_INDEX_BUFFER_HPP__
#define __ERE_OPENGL_INDEX_BUFFER_HPP__

#include <ere/ere_config.hpp>
#include <ere/api/index_buffer_api.hpp>

#ifdef USE_OPENGL

namespace ere {

class opengl_index_buffer : public index_buffer_api {
public:
    opengl_index_buffer(uint32_t t_size);
    opengl_index_buffer(uint32_t* t_data, uint32_t t_size);

    virtual ~opengl_index_buffer();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void set_data(const uint32_t* t_data, uint32_t t_size) override;

private:

    unsigned int m_IBO;

};

}

#endif

#endif

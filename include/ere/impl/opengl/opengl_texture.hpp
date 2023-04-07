#ifndef __ERE_OPENGL_TEXTURE_HPP__
#define __ERE_OPENGL_TEXTURE_HPP__

#include <ere/core/core.hpp>
#include <ere/ere_config.hpp>
#include <ere/api/texture_api.hpp>

#ifdef USE_OPENGL

namespace ere {

class opengl_texture : public texture_api {
public:

    opengl_texture(const std::string& path);
    opengl_texture(size_t size, uint32_t width, uint32_t height);
    opengl_texture(unsigned char* data, size_t size, uint32_t width, uint32_t height);
    ~opengl_texture() override;

    void bind(uint32_t slot) const override;
    void unbind() const override;

    void set_data(unsigned char* data, size_t size, uint32_t width, uint32_t height) override;

};

}

#endif // USE_OPENGL


#endif // __ERE_OPENGL_TEXTURE_HPP__

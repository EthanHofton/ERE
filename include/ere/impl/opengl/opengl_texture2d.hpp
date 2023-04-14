#ifndef __ERE_OPENGL_TEXTURE_HPP__
#define __ERE_OPENGL_TEXTURE_HPP__

#include <ere/core/core.hpp>
#include <ere/ere_config.hpp>
#include <ere/api/texture2d_api.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>
#include "opengl_texture_conversions.hpp"

namespace ere {

class opengl_texture2d : public texture2d_api {
public:

    opengl_texture2d(const std::string& path);
    opengl_texture2d(const texture_api::format& t_format, uint32_t width, uint32_t height);
    opengl_texture2d(unsigned char* data, const texture_api::format& t_format, uint32_t width, uint32_t height);
    virtual ~opengl_texture2d() override;

    virtual void bind(uint32_t slot) const override;
    virtual void unbind() const override;

    virtual void set_data(unsigned char* data, const texture_api::format& t_format, uint32_t width, uint32_t height) override;

    virtual void set_min_filter(texture_api::filter min_filter) override;
    virtual void set_mag_filter(texture_api::filter mag_filter) override;

    virtual void set_wrap(texture_api::wrap wrap) override;
    virtual void set_wrap(texture_api::wrap wrap_s, texture_api::wrap wrap_t) override;
    virtual void set_wrap_s(texture_api::wrap wrap_s) override;
    virtual void set_wrap_t(texture_api::wrap wrap_t) override;

};

}

#endif // USE_OPENGL


#endif // __ERE_OPENGL_TEXTURE_HPP__

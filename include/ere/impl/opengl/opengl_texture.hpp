#ifndef __ERE_OPENGL_TEXTURE_HPP__
#define __ERE_OPENGL_TEXTURE_HPP__

#include <ere/core/core.hpp>
#include <ere/ere_config.hpp>
#include <ere/api/texture_api.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

class opengl_texture : public texture_api {
public:

    opengl_texture(const std::string& path);
    opengl_texture(const texture_api::format& t_format, uint32_t width, uint32_t height);
    opengl_texture(unsigned char* data, const texture_api::format& t_format, uint32_t width, uint32_t height);
    virtual ~opengl_texture() override;

    virtual void bind(uint32_t slot) const override;
    virtual void unbind() const override;

    virtual void set_data(unsigned char* data, const texture_api::format& t_format, uint32_t width, uint32_t height) override;

    virtual void set_min_filter(texture_api::filter min_filter) override;
    virtual void set_mag_filter(texture_api::filter mag_filter) override;
    virtual void set_wrap(texture_api::wrap wrap_s, texture_api::wrap wrap_t, texture_api::wrap wrap_r) override;
    virtual void set_wrap(texture_api::wrap wrap_s, texture_api::wrap wrap_t) override;
    virtual void set_wrap(texture_api::wrap wrap) override;

private:

    unsigned int get_depth_from_format(const texture_api::format& t_format) const;
    GLenum get_gl_format(const texture_api::format& t_format) const;
    GLenum get_gl_internal_format(const texture_api::format& t_format) const;
    GLenum get_gl_filter(const texture_api::filter& t_filter) const;
    GLenum get_gl_wrap(const texture_api::wrap& t_wrap) const;
    GLenum get_gl_type(const texture_api::format& t_format) const;
};

}

#endif // USE_OPENGL


#endif // __ERE_OPENGL_TEXTURE_HPP__

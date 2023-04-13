#ifndef __ERE_OPENGL_CUBEMAP_HPP__
#define __ERE_OPENGL_CUBEMAP_HPP__

#include <ere/api/cubemap_api.hpp>

#include <ere/ere_config.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>
#include "opengl_texture_conversions.hpp"

namespace ere {

class opengl_cubemap : public cubemap_api {
public:

    opengl_cubemap(const std::vector<std::string>& paths);
    opengl_cubemap(const std::vector<format>& t_formats, const std::vector<glm::ivec2>& sizes);
    opengl_cubemap(const std::vector<unsigned char*>& data, const std::vector<format>& t_formats, const std::vector<glm::ivec2>& sizes);
    virtual ~opengl_cubemap() override;

    virtual void bind(uint32_t slot) const override;
    virtual void unbind() const override;

    virtual void set_min_filter(texture_api::filter min_filter) override;
    virtual void set_mag_filter(texture_api::filter mag_filter) override;

    virtual void set_wrap(texture_api::wrap wrap) override;
    virtual void set_wrap(texture_api::wrap wrap_s, texture_api::wrap wrap_t, texture_api::wrap wrap_r) override;
    virtual void set_wrap_s(texture_api::wrap wrap_s) override;
    virtual void set_wrap_t(texture_api::wrap wrap_t) override;
    virtual void set_wrap_r(texture_api::wrap wrap_r) override;

    virtual void set_data(const std::vector<unsigned char*>& data, const std::vector<format>& t_formats, const std::vector<glm::ivec2>& sizes) override;
};

}

#endif

#endif // __ERE_OPENGL_CUBEMAP_HPP__

#ifndef __ERE_TEXTURE_API_HPP__
#define __ERE_TEXTURE_API_HPP__

#include <ere/core/core.hpp>
#include <string>

namespace ere {

class texture_api {
public:

    enum class format {
        RED,
        RG,
        RGB,
        RGB16F,
        RGB32F,
        RGBA,
        RGBA16F,
        RGBA32F,
        DEPTH,
        STENCIL,
        DEPTH_STENCIL
    };

    enum class filter {
        NEAREST,
        LINEAR,
        NEAREST_MIPMAP_NEAREST,
        LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR,
        LINEAR_MIPMAP_LINEAR
    };

    enum class wrap {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER
    };

    virtual ~texture_api() = default;

    virtual void bind(uint32_t slot) const = 0;
    virtual void unbind() const = 0;

    inline void set_uniform_name(const std::string& name) { m_uniform_name = name; }
    inline const std::string& get_uniform_name() const { return m_uniform_name; }

    inline unsigned int get_texture_id() const { return m_texture_id; }

protected:

    std::string m_uniform_name = "texture";
    unsigned int m_texture_id = 0;

};

}

#endif

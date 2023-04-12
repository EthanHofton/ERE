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
        RGBA,
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

    virtual void set_data(unsigned char* data, const format& t_format, uint32_t width, uint32_t height) = 0;

    inline void set_uniform_name(const std::string& name) { m_uniform_name = name; }
    inline const std::string& get_uniform_name() const { return m_uniform_name; }

    inline uint32_t get_width() const { return m_width; }
    inline uint32_t get_height() const { return m_height; }
    inline uint32_t get_depth() const { return m_depth; }
    inline unsigned int get_texture_id() const { return m_texture_id; }
    inline format get_format() const { return m_format; }
    inline filter get_min_filter() const { return m_min_filter; }
    inline filter get_mag_filter() const { return m_mag_filter; }
    inline wrap get_wrap() const { return m_wrap; }

    virtual void set_min_filter(filter min_filter) = 0;
    virtual void set_mag_filter(filter mag_filter) = 0;
    virtual void set_wrap(wrap wrap_s, wrap wrap_t, wrap wrap_r) = 0;
    virtual void set_wrap(wrap wrap_s, wrap wrap_t) = 0;
    virtual void set_wrap(wrap wrap) = 0;

    static ref<texture_api> create_texture_api(const std::string& path);
    static ref<texture_api> create_texture_api(const format& t_format, uint32_t width, uint32_t height);
    static ref<texture_api> create_texture_api(unsigned char* data, const format& format, uint32_t width, uint32_t height);

protected:

    std::string m_uniform_name;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_depth;
    format m_format;

    filter m_min_filter = filter::NEAREST_MIPMAP_LINEAR;
    filter m_mag_filter = filter::LINEAR;
    wrap m_wrap = wrap::REPEAT;

    unsigned int m_texture_id;

};

}

#endif

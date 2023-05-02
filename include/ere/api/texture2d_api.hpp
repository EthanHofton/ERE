#ifndef __ERE_TEXTURE2D_API_HPP__
#define __ERE_TEXTURE2D_API_HPP__

#include "texture_api.hpp"

namespace ere {

class texture2d_api : public texture_api {
public:

    virtual ~texture2d_api() = default;

    virtual void bind(uint32_t slot) const = 0;
    virtual void unbind() const = 0;

    virtual void set_data(unsigned char* data, const format& t_format, uint32_t width, uint32_t height) = 0;

    inline uint32_t get_width() const { return m_width; }
    inline uint32_t get_height() const { return m_height; }
    inline format get_format() const { return m_format; }

    inline filter get_min_filter() const { return m_min_filter; }
    inline filter get_mag_filter() const { return m_mag_filter; }

    inline wrap get_wrap_s() const { return m_wrap_s; }
    inline wrap get_wrap_t() const { return m_wrap_t; }

    virtual void set_min_filter(filter min_filter) = 0;
    virtual void set_mag_filter(filter mag_filter) = 0;

    virtual void set_wrap(wrap wrap) = 0;
    virtual void set_wrap(wrap wrap_s, wrap wrap_t) = 0;
    virtual void set_wrap_s(wrap wrap_s) = 0;
    virtual void set_wrap_t(wrap wrap_t) = 0;

    static ref<texture2d_api> create_texture2d_api(const std::string& path, bool flip_on_load = true);
    static ref<texture2d_api> create_texture2d_api(const format& t_format, uint32_t width, uint32_t height);
    static ref<texture2d_api> create_texture2d_api(unsigned char* data, const format& format, uint32_t width, uint32_t height);

protected:

    std::string m_uniform_name;

    uint32_t m_width;
    uint32_t m_height;
    format m_format;

    filter m_min_filter = filter::NEAREST_MIPMAP_LINEAR;
    filter m_mag_filter = filter::LINEAR;

    wrap m_wrap_s = wrap::REPEAT;
    wrap m_wrap_t = wrap::REPEAT;
};

}

#endif

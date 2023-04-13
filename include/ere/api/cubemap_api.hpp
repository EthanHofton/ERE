#ifndef __ERE_CUBEMAP_API__
#define __ERE_CUBEMAP_API__

#include "texture_api.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace ere {

class cubemap_api : public texture_api {
public:
   
    virtual ~cubemap_api();

    virtual void bind(uint32_t slot) const = 0;
    virtual void unbind() const = 0;

    inline int get_width(int index = 0) const { return m_sizes[index].x; }
    inline int get_height(int index = 0) const { return m_sizes[index].y; }
    inline glm::ivec2 get_size(int index = 0) const { return m_sizes[index]; }
    inline std::vector<glm::ivec2> get_sizes() const { return m_sizes; }

    inline format get_format(int index = 0) const { return m_formats[index]; }
    inline std::vector<format> get_formats() const { return m_formats; }

    inline filter get_min_filter() const { return m_min_filter; }
    inline filter get_mag_filter() const { return m_mag_filter; }

    inline wrap get_wrap_s() const { return m_wrap_s; }
    inline wrap get_wrap_t() const { return m_wrap_t; }
    inline wrap get_wrap_r() const { return m_wrap_r; }

    virtual void set_min_filter(filter min_filter) = 0;
    virtual void set_mag_filter(filter mag_filter) = 0;

    virtual void set_wrap(wrap wrap) = 0;
    virtual void set_wrap(wrap wrap_s, wrap wrap_t, wrap wrap_r) = 0;
    virtual void set_wrap_s(wrap wrap_s) = 0;
    virtual void set_wrap_t(wrap wrap_t) = 0;
    virtual void set_wrap_r(wrap wrap_r) = 0;

    virtual void set_data(const std::vector<unsigned char*>& data, const std::vector<format>& formats, const std::vector<glm::ivec2>& sizes) = 0;

    static ref<cubemap_api> create_cubemap_api(const std::vector<std::string>& paths);
    static ref<cubemap_api> create_cubemap_api(const std::vector<format> t_formats, const std::vector<glm::ivec2> sizes);
    static ref<cubemap_api> create_cubemap_api(const std::vector<unsigned char*>& data, const std::vector<format> formats, const std::vector<glm::ivec2> sizes);

protected:

    std::vector<glm::ivec2> m_sizes;
    std::vector<format> m_formats;

    filter m_min_filter = filter::NEAREST_MIPMAP_LINEAR;
    filter m_mag_filter = filter::LINEAR;

    wrap m_wrap_s = wrap::REPEAT;
    wrap m_wrap_t = wrap::REPEAT;
    wrap m_wrap_r = wrap::REPEAT;

};

}

#endif // __ERE_CUBEMAP_API__

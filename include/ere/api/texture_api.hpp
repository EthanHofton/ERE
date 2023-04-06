#ifndef __ERE_TEXTURE_API_HPP__
#define __ERE_TEXTURE_API_HPP__

#include <ere/core/core.hpp>
#include <string>

namespace ere {

class texture_api {
public:

    virtual ~texture_api() = default;

    virtual void bind(uint32_t slot) const = 0;
    virtual void unbind() const = 0;

    virtual void set_data(unsigned char* data, size_t size, uint32_t width, uint32_t height) = 0;

    inline void set_uniform_name(const std::string& name) { m_uniform_name = name; }
    inline const std::string& get_uniform_name() const { return m_uniform_name; }

    inline uint32_t get_width() const { return m_width; }
    inline uint32_t get_height() const { return m_height; }
    inline uint32_t get_depth() const { return m_depth; }

    static ref<texture_api> create_texture_api(const std::string& path);
    static ref<texture_api> create_texture_api(size_t size, uint32_t width, uint32_t height);
    static ref<texture_api> create_texture_api(unsigned char* data, size_t size, uint32_t width, uint32_t height);

protected:

    std::string m_uniform_name;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_depth;

};

}

#endif

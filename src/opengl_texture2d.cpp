#include <ere/impl/opengl/opengl_texture2d.hpp>
#include <stb_image.h>
#include <ere/core/logger.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

ref<texture2d_api> texture2d_api::create_texture2d_api(const std::string& path) {
    return std::make_shared<opengl_texture2d>(path);
}

ref<texture2d_api> texture2d_api::create_texture2d_api(const format& t_format, uint32_t width, uint32_t height) {
    return std::make_shared<opengl_texture2d>(t_format, width, height);
}

ref<texture2d_api> texture2d_api::create_texture2d_api(unsigned char* data, const format& t_format, uint32_t width, uint32_t height) {
    return std::make_shared<opengl_texture2d>(data, t_format, width, height);
}

opengl_texture2d::opengl_texture2d(const std::string& path) {
    m_width = 0;
    m_height = 0;
    m_texture_id = 0;
    int depth;

    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(path.c_str(), (int*)&m_width, (int*)&m_height, (int*)&depth, 0);

    if (data) {
        if (depth == 1) {
            m_format = texture_api::format::RED;
        } else if (depth == 3) {
            m_format = texture_api::format::RGB;
        } else if (depth == 4) {
            m_format = texture_api::format::RGBA;
        }

        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);

        set_min_filter(texture_api::filter::LINEAR);
        set_mag_filter(texture_api::filter::LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, get_gl_internal_format(m_format), m_width, m_height, 0, get_gl_format(m_format), get_gl_type(m_format), data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        ERE_ERROR("Failed to load texture: " + path);
    }
}

opengl_texture2d::opengl_texture2d(const texture_api::format& t_format, uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
    m_format = t_format;
    m_texture_id = 0;

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    set_min_filter(texture_api::filter::LINEAR);
    set_mag_filter(texture_api::filter::LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, get_gl_internal_format(m_format), m_width, m_height, 0, get_gl_format(m_format), get_gl_type(m_format), nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);
}

opengl_texture2d::opengl_texture2d(unsigned char* data, const texture_api::format& t_format, uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
    m_format = t_format;
    m_texture_id = 0;

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    set_min_filter(texture_api::filter::LINEAR);
    set_mag_filter(texture_api::filter::LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, get_gl_internal_format(m_format), m_width, m_height, 0, get_gl_format(m_format), get_gl_type(m_format), data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

opengl_texture2d::~opengl_texture2d() {
    glDeleteTextures(1, &m_texture_id);
}

void opengl_texture2d::bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void opengl_texture2d::unbind() const {
    glActiveTexture(GL_TEXTURE0);
}

void opengl_texture2d::set_data(unsigned char* data, const texture_api::format& t_format, uint32_t width, uint32_t height) {

    m_width = width;
    m_height = height;
    m_format = t_format;

    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, get_gl_format(m_format), get_gl_type(m_format), data);
}

void opengl_texture2d::set_min_filter(texture_api::filter filter) {
    m_min_filter = filter;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, get_gl_filter(filter));
}

void opengl_texture2d::set_mag_filter(texture_api::filter filter) {
    m_mag_filter = filter;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, get_gl_filter(filter));
}

void opengl_texture2d::set_wrap(texture_api::wrap wrap) {
    m_wrap_s = wrap;
    m_wrap_t = wrap;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, get_gl_wrap(m_wrap_s));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, get_gl_wrap(m_wrap_t));
}

void opengl_texture2d::set_wrap(texture_api::wrap s_wrap, texture_api::wrap t_wrap) {
    m_wrap_s = s_wrap;
    m_wrap_t = t_wrap;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, get_gl_wrap(m_wrap_s));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, get_gl_wrap(m_wrap_t));
}

void opengl_texture2d::set_wrap_s(texture_api::wrap wrap) {
    m_wrap_s = wrap;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, get_gl_wrap(m_wrap_s));
}

void opengl_texture2d::set_wrap_t(texture_api::wrap wrap) {
    m_wrap_t = wrap;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, get_gl_wrap(m_wrap_t));
}

}

#endif // USE_OPENGL

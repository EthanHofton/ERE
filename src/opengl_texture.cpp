#include <ere/impl/opengl/opengl_texture.hpp>
#include <stb_image.h>
#include <ere/core/logger.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

ref<texture_api> texture_api::create_texture_api(const std::string& path) {
    return std::make_shared<opengl_texture>(path);
}

ref<texture_api> texture_api::create_texture_api(const format& t_format, uint32_t width, uint32_t height) {
    return std::make_shared<opengl_texture>(t_format, width, height);
}

ref<texture_api> texture_api::create_texture_api(unsigned char* data, const format& t_format, uint32_t width, uint32_t height) {
    return std::make_shared<opengl_texture>(data, t_format, width, height);
}

opengl_texture::opengl_texture(const std::string& path) {
    m_width = 0;
    m_height = 0;
    m_depth = 0;
    m_texture_id = 0;

    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(path.c_str(), (int*)&m_width, (int*)&m_height, (int*)&m_depth, 0);

    if (data) {
        if (m_depth == 1) {
            m_format = texture_api::format::RED;
        } else if (m_depth == 3) {
            m_format = texture_api::format::RGB;
        } else if (m_depth == 4) {
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

opengl_texture::opengl_texture(const texture_api::format& t_format, uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
    m_depth = get_depth_from_format(t_format);
    m_format = t_format;
    m_texture_id = 0;

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    set_min_filter(texture_api::filter::LINEAR);
    set_mag_filter(texture_api::filter::LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, get_gl_internal_format(m_format), m_width, m_height, 0, get_gl_format(m_format), get_gl_type(m_format), nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);
}

opengl_texture::opengl_texture(unsigned char* data, const texture_api::format& t_format, uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
    m_format = t_format;
    m_depth = get_depth_from_format(t_format);
    m_texture_id = 0;

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    set_min_filter(texture_api::filter::LINEAR);
    set_mag_filter(texture_api::filter::LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, get_gl_internal_format(m_format), m_width, m_height, 0, get_gl_format(m_format), get_gl_type(m_format), data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

opengl_texture::~opengl_texture() {
    glDeleteTextures(1, &m_texture_id);
}

void opengl_texture::bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void opengl_texture::unbind() const {
    glActiveTexture(GL_TEXTURE0);
}

void opengl_texture::set_data(unsigned char* data, const texture_api::format& t_format, uint32_t width, uint32_t height) {

    m_width = width;
    m_height = height;
    m_format = t_format;
    m_depth = get_depth_from_format(t_format);

    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, get_gl_format(m_format), get_gl_type(m_format), data);
}

void opengl_texture::set_min_filter(texture_api::filter filter) {
    m_min_filter = filter;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, get_gl_filter(filter));
}

void opengl_texture::set_mag_filter(texture_api::filter filter) {
    m_mag_filter = filter;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, get_gl_filter(filter));
}

void opengl_texture::set_wrap(texture_api::wrap wrap) {
    m_wrap = wrap;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, get_gl_wrap(wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, get_gl_wrap(wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, get_gl_wrap(wrap));
}

void opengl_texture::set_wrap(texture_api::wrap s_wrap, texture_api::wrap t_wrap) {
    m_wrap = s_wrap;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, get_gl_wrap(s_wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, get_gl_wrap(t_wrap));
}

void opengl_texture::set_wrap(texture_api::wrap s_wrap, texture_api::wrap t_wrap, texture_api::wrap r_wrap) {
    m_wrap = s_wrap;
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, get_gl_wrap(s_wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, get_gl_wrap(t_wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, get_gl_wrap(r_wrap));
}

unsigned int opengl_texture::get_depth_from_format(const texture_api::format& format) const {
    switch (format) {
        case texture_api::format::RED:
        case texture_api::format::DEPTH:
        case texture_api::format::STENCIL:
            return 1;
        case texture_api::format::RG:
        case texture_api::format::DEPTH_STENCIL:
            return 2;
        case texture_api::format::RGB:
        case texture_api::format::RGB16F:
        case texture_api::format::RGB32F:
            return 3;
        case texture_api::format::RGBA:
        case texture_api::format::RGBA16F:
        case texture_api::format::RGBA32F:
            return 4;
        default:
            return 4;
    }
}

GLenum opengl_texture::get_gl_format(const texture_api::format& format) const {
    switch (format) {
        case texture_api::format::RED:
            return GL_RED;
        case texture_api::format::RG:
            return GL_RG;
        case texture_api::format::RGB:
        case texture_api::format::RGB16F:
        case texture_api::format::RGB32F:
            return GL_RGB;
        case texture_api::format::RGBA:
        case texture_api::format::RGBA16F:
        case texture_api::format::RGBA32F:
            return GL_RGBA;
        case texture_api::format::DEPTH:
            return GL_DEPTH_COMPONENT;
        case texture_api::format::STENCIL:
            return GL_STENCIL_INDEX;
        case texture_api::format::DEPTH_STENCIL:
            return GL_DEPTH_STENCIL;
        default:
            return GL_RGBA;
    }
}

GLenum opengl_texture::get_gl_internal_format(const texture_api::format& format) const {
    switch (format) {
        case texture_api::format::RED:
            return GL_RED;
        case texture_api::format::RG:
            return GL_RG;
        case texture_api::format::RGB:
            return GL_RGB;
        case texture_api::format::RGB16F:
            return GL_RGB16F;
        case texture_api::format::RGB32F:
            return GL_RGB32F;
        case texture_api::format::RGBA:
            return GL_RGBA;
        case texture_api::format::RGBA16F:
            return GL_RGBA16F;
        case texture_api::format::RGBA32F:
            return GL_RGBA32F;
        case texture_api::format::DEPTH:
            return GL_DEPTH_COMPONENT;
        case texture_api::format::STENCIL:
            return GL_STENCIL_INDEX;
        case texture_api::format::DEPTH_STENCIL:
            return GL_DEPTH_STENCIL;
        default:
            return GL_RGBA;
    }
}

GLenum opengl_texture::get_gl_filter(const texture_api::filter& filter) const {
    switch (filter) {
        case texture_api::filter::LINEAR:
            return GL_LINEAR;
        case texture_api::filter::NEAREST:
            return GL_NEAREST;
        case texture_api::filter::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        case texture_api::filter::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case texture_api::filter::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case texture_api::filter::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        default:
            return GL_LINEAR;
    }
}

GLenum opengl_texture::get_gl_wrap(const texture_api::wrap& wrap) const {
    switch (wrap) {
        case texture_api::wrap::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case texture_api::wrap::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        case texture_api::wrap::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case texture_api::wrap::REPEAT:
            return GL_REPEAT;
        default:
            return GL_REPEAT;
    }
}

GLenum opengl_texture::get_gl_type(const texture_api::format& format) const {
    switch (format) {
        case texture_api::format::RED:
        case texture_api::format::RG:
        case texture_api::format::RGB:
        case texture_api::format::RGBA:
        case texture_api::format::DEPTH:
        case texture_api::format::STENCIL:
            return GL_UNSIGNED_BYTE;
        case texture_api::format::DEPTH_STENCIL:
            return GL_UNSIGNED_INT_24_8;
        case texture_api::format::RGB16F:
        case texture_api::format::RGB32F:
        case texture_api::format::RGBA16F:
        case texture_api::format::RGBA32F:
            return GL_FLOAT;
        default:
            return GL_UNSIGNED_BYTE;
    }


}

}

#endif // USE_OPENGL

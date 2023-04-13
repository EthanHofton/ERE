#include <ere/ere_config.hpp>

#ifdef USE_OPENGL
#include <ere/impl/opengl/opengl_cubemap.hpp>
#include <stb_image.h>
#include <ere/core/logger.hpp>

namespace ere {

ref<cubemap_api> cubemap_api::create_cubemap_api(const std::vector<std::string> &paths) {
    return std::make_shared<opengl_cubemap>(paths);
}

ref<cubemap_api> cubemap_api::create_cubemap_api(const std::vector<format> t_formats, const std::vector<glm::ivec2> sizes) {
    return std::make_shared<opengl_cubemap>(t_formats, sizes);
}

ref<cubemap_api> cubemap_api::create_cubemap_api(const std::vector<unsigned char *> &data, const std::vector<format> formats, const std::vector<glm::ivec2> sizes) {
    return std::make_shared<opengl_cubemap>(data, formats, sizes);
}

opengl_cubemap::opengl_cubemap(const std::vector<std::string>& paths) {
    if (paths.size() != 6) {
        ERE_ERROR("Cubemap texture must have 6 faces, but only {} were provided", paths.size());
        return;
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

    int width, height, nr_channels;
    for (uint32_t i = 0; i < paths.size(); i++) {
        stbi_set_flip_vertically_on_load(0);
        unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &nr_channels, 0);
        format format;
        if (nr_channels == 1) {
            format = format::RED;
        } else if (nr_channels == 3) {
            format = format::RGB;
        } else if (nr_channels == 4) {
            format = format::RGBA;
        }
        m_formats.push_back(format);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, get_gl_internal_format(format), width, height, 0, get_gl_format(format), get_gl_type(format), data);
            m_sizes.push_back(glm::ivec2(width, height));
            stbi_image_free(data);
        } else {
            ERE_ERROR("Cubemap texture failed to load at path: {}", paths[i]);
            stbi_image_free(data);
        }
    }

    set_min_filter(filter::LINEAR);
    set_mag_filter(filter::LINEAR);
    set_wrap_s(wrap::CLAMP_TO_EDGE);
    set_wrap_t(wrap::CLAMP_TO_EDGE);
    set_wrap_r(wrap::CLAMP_TO_EDGE);
}

opengl_cubemap::opengl_cubemap(const std::vector<format>& t_formats, const std::vector<glm::ivec2>& sizes) {
    if (t_formats.size() != 6 || sizes.size() != 6) {
        ERE_ERROR("Cubemap texture must have 6 faces, but only {} were provided", t_formats.size());
        return;
    }

    m_formats = t_formats;
    m_sizes = sizes;

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

    for (uint32_t i = 0; i < t_formats.size(); i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, get_gl_internal_format(m_formats[i]), m_sizes[i].x, m_sizes[i].y, 0, get_gl_format(m_formats[i]), get_gl_type(m_formats[i]), nullptr);
    }

    set_min_filter(filter::LINEAR);
    set_mag_filter(filter::LINEAR);
    set_wrap_s(wrap::CLAMP_TO_EDGE);
    set_wrap_t(wrap::CLAMP_TO_EDGE);
    set_wrap_r(wrap::CLAMP_TO_EDGE);
}

opengl_cubemap::opengl_cubemap(const std::vector<unsigned char*>& data, const std::vector<format>& t_formats, const std::vector<glm::ivec2>& sizes) {
    if (t_formats.size() != 6 || sizes.size() != 6 || data.size() != 6) {
        ERE_ERROR("Cubemap texture must have 6 faces, but only {} were provided", t_formats.size());
        return;
    }

    m_formats = t_formats;
    m_sizes = sizes;

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

    for (uint32_t i = 0; i < t_formats.size(); i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, get_gl_internal_format(m_formats[i]), m_sizes[i].x, m_sizes[i].y, 0, get_gl_format(m_formats[i]), get_gl_type(m_formats[i]), data[i]);
    }

    set_min_filter(filter::LINEAR);
    set_mag_filter(filter::LINEAR);
    set_wrap_s(wrap::CLAMP_TO_EDGE);
    set_wrap_t(wrap::CLAMP_TO_EDGE);
    set_wrap_r(wrap::CLAMP_TO_EDGE);
}

opengl_cubemap::~opengl_cubemap() {
    glDeleteTextures(1, &m_texture_id);
}

void opengl_cubemap::bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
}

void opengl_cubemap::unbind() const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void opengl_cubemap::set_min_filter(filter filter) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, get_gl_filter(filter));
}

void opengl_cubemap::set_mag_filter(filter filter) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, get_gl_filter(filter));
}

void opengl_cubemap::set_wrap(texture_api::wrap wrap) {
    set_wrap_s(wrap);
    set_wrap_t(wrap);
    set_wrap_r(wrap);
}

void opengl_cubemap::set_wrap(texture_api::wrap wrap_s, texture_api::wrap wrap_t, texture_api::wrap wrap_r) {
    set_wrap_s(wrap_s);
    set_wrap_t(wrap_t);
    set_wrap_r(wrap_r);
}

void opengl_cubemap::set_wrap_s(wrap wrap) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, get_gl_wrap(wrap));
}

void opengl_cubemap::set_wrap_t(wrap wrap) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, get_gl_wrap(wrap));
}

void opengl_cubemap::set_wrap_r(wrap wrap) {
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, get_gl_wrap(wrap));
}

void opengl_cubemap::set_data(const std::vector<unsigned char*>& data, const std::vector<format>& t_formats, const std::vector<glm::ivec2>& sizes) {
    if (t_formats.size() != 6 || sizes.size() != 6 || data.size() != 6) {
        ERE_ERROR("Cubemap texture must have 6 faces, but only {} were provided", t_formats.size());
        return;
    }

    m_formats = t_formats;
    m_sizes = sizes;

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

    for (uint32_t i = 0; i < t_formats.size(); i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, get_gl_internal_format(m_formats[i]), m_sizes[i].x, m_sizes[i].y, 0, get_gl_format(m_formats[i]), get_gl_type(m_formats[i]), data[i]);
    }
}

}

#endif

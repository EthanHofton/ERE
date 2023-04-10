#include <ere/impl/opengl/opengl_texture.hpp>
#include <stb_image.h>
#include <ere/core/logger.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

ref<texture_api> texture_api::create_texture_api(const std::string& path) {
    return std::make_shared<opengl_texture>(path);
}

ref<texture_api> texture_api::create_texture_api(size_t size, uint32_t width, uint32_t height) {
    return std::make_shared<opengl_texture>(size, width, height);
}

ref<texture_api> texture_api::create_texture_api(unsigned char* data, size_t size, uint32_t width, uint32_t height) {
    return std::make_shared<opengl_texture>(data, size, width, height);
}

opengl_texture::opengl_texture(const std::string& path) {
    m_width = 0;
    m_height = 0;
    m_depth = 0;
    m_texture_id = 0;

    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(path.c_str(), (int*)&m_width, (int*)&m_height, (int*)&m_depth, 0);

    if (data) {
        GLenum format;
        if (m_depth == 1) {
            format = GL_RED;
        } else if (m_depth == 3) {
            format = GL_RGB;
        } else if (m_depth == 4) {
            format = GL_RGBA;
        }

        glGenTextures(1, &m_texture_id);
        glBindTexture(GL_TEXTURE_2D, m_texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    } else {
        ERE_ERROR("Failed to load texture: " + path);
    }
}

opengl_texture::opengl_texture(size_t size, uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
    m_depth = (uint32_t)(size / sizeof(unsigned char)) / (width * height);
    m_texture_id = 0;

    GLenum format;
    if (m_depth == 1) {
        format = GL_RED;
    } else if (m_depth == 3) {
        format = GL_RGB;
    } else if (m_depth == 4) {
        format = GL_RGBA;
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, nullptr);
    glGenerateMipmap(GL_TEXTURE_2D);
}

opengl_texture::opengl_texture(unsigned char* data, size_t size, uint32_t width, uint32_t height) {
    m_width = width;
    m_height = height;
    m_depth = (uint32_t)(size / sizeof(unsigned char)) / (width * height);
    m_texture_id = 0;

    GLenum format;
    if (m_depth == 1) {
        format = GL_RED;
    } else if (m_depth == 3) {
        format = GL_RGB;
    } else if (m_depth == 4) {
        format = GL_RGBA;
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
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

void opengl_texture::set_data(unsigned char* data, size_t size, uint32_t width, uint32_t height) {

    m_width = width;
    m_height = height;
    m_depth = (uint32_t)(size / sizeof(unsigned char)) / (width * height);

    GLenum format;
    if (m_depth == 1) {
        format = GL_RED;
    } else if (m_depth == 3) {
        format = GL_RGB;
    } else if (m_depth == 4) {
        format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);
}

}

#endif // USE_OPENGL

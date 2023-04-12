#include <ere/impl/opengl/opengl_framebuffer.hpp>
#include <ere/core/logger.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

ref<framebuffer_api> framebuffer_api::create_framebuffer_api(int t_width, int t_height) {
    return std::make_shared<opengl_framebuffer>(t_width, t_height);
}

opengl_framebuffer::opengl_framebuffer(int t_width, int t_height) {
    m_width = t_width;
    m_height = t_height;

    glGenFramebuffers(1, &m_id);
}

opengl_framebuffer::~opengl_framebuffer() {
    glDeleteFramebuffers(1, &m_id);
    if (m_rbo_id != 0) {
        glDeleteRenderbuffers(1, &m_rbo_id);
    }
}

void opengl_framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void opengl_framebuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void opengl_framebuffer::disable_color_attachment() const {
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
}

int opengl_framebuffer::get_id() const {
    return m_id;
}

int opengl_framebuffer::get_width() const {
    return m_width;
}

int opengl_framebuffer::get_height() const {
    return m_height;
}

bool opengl_framebuffer::is_valid() const {
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

ref<texture_api> opengl_framebuffer::add_color_attachment() {
    m_color_attachment = texture_api::create_texture_api(texture_api::format::RGB, m_width, m_height);
    m_color_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_color_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_color_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_color_attachment->get_texture_id(), 0);

    return m_color_attachment;
}

ref<texture_api> opengl_framebuffer::add_depth_attachment() {
    m_depth_attachment = texture_api::create_texture_api(texture_api::format::DEPTH, m_width, m_height);
    m_depth_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_depth_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_depth_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_attachment->get_texture_id(), 0);

    return m_depth_attachment;
}

ref<texture_api> opengl_framebuffer::add_stencil_attachment() {
    m_stencil_attachment = texture_api::create_texture_api(texture_api::format::STENCIL, m_width, m_height);
    m_stencil_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_stencil_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_stencil_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_stencil_attachment->get_texture_id(), 0);

    return m_stencil_attachment;
}

ref<texture_api> opengl_framebuffer::add_depth_stencil_attachment() {
    m_depth_stencil_attachment = texture_api::create_texture_api(texture_api::format::DEPTH_STENCIL, m_width, m_height);
    m_depth_stencil_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_depth_stencil_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_depth_stencil_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_stencil_attachment->get_texture_id(), 0);

    return m_depth_stencil_attachment;
}

void opengl_framebuffer::add_depth_stencil_attachment_write_only() {
    glGenRenderbuffers(1, &m_rbo_id);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo_id);
}


}

#endif // USE_OPENGL

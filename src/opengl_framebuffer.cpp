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
    bind();
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    unbind();
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

void opengl_framebuffer::resize(int t_width, int t_height) {
    m_width = t_width;
    m_height = t_height;

    // delete framebuffer
    glDeleteFramebuffers(1, &m_id);

    // create new framebuffer
    glGenFramebuffers(1, &m_id);

    std::vector<ref<texture2d_api>> color_attachments = m_color_attachments;
    m_color_attachments.clear();
    for (auto& color_attachment : color_attachments) {
        std::string uniform_name = color_attachment->get_uniform_name();
        texture_api::wrap w_s = color_attachment->get_wrap_s();
        texture_api::wrap w_t = color_attachment->get_wrap_t();
        texture_api::filter mag_f = color_attachment->get_mag_filter();
        texture_api::filter min_f = color_attachment->get_min_filter();
        add_color_attachment();
        color_attachment->set_uniform_name(uniform_name);
        color_attachment->set_wrap(w_s, w_t);
        color_attachment->set_mag_filter(mag_f);
        color_attachment->set_min_filter(min_f);
    }
    if (m_depth_attachment != nullptr) {
        std::string uniform_name = m_depth_attachment->get_uniform_name();
        texture_api::wrap w_s = m_depth_attachment->get_wrap_s();
        texture_api::wrap w_t = m_depth_attachment->get_wrap_t();
        texture_api::filter mag_f = m_depth_attachment->get_mag_filter();
        texture_api::filter min_f = m_depth_attachment->get_min_filter();
        add_depth_attachment();
        m_depth_attachment->set_uniform_name(uniform_name);
        m_depth_attachment->set_wrap(w_s, w_t);
        m_depth_attachment->set_mag_filter(mag_f);
        m_depth_attachment->set_min_filter(min_f);
    }
    if (m_stencil_attachment != nullptr) {
        std::string uniform_name = m_stencil_attachment->get_uniform_name();
        texture_api::wrap w_s = m_stencil_attachment->get_wrap_s();
        texture_api::wrap w_t = m_stencil_attachment->get_wrap_t();
        texture_api::filter mag_f = m_stencil_attachment->get_mag_filter();
        texture_api::filter min_f = m_stencil_attachment->get_min_filter();
        add_stencil_attachment();
        m_stencil_attachment->set_uniform_name(uniform_name);
        m_stencil_attachment->set_wrap(w_s, w_t);
        m_stencil_attachment->set_mag_filter(mag_f);
        m_stencil_attachment->set_min_filter(min_f);
    }
    if (m_depth_stencil_attachment != nullptr) {
        std::string uniform_name = m_depth_stencil_attachment->get_uniform_name();
        texture_api::wrap w_s = m_depth_stencil_attachment->get_wrap_s();
        texture_api::wrap w_t = m_depth_stencil_attachment->get_wrap_t();
        texture_api::filter mag_f = m_depth_stencil_attachment->get_mag_filter();
        texture_api::filter min_f = m_depth_stencil_attachment->get_min_filter();
        add_depth_stencil_attachment();
        m_depth_stencil_attachment->set_uniform_name(uniform_name);
        m_depth_stencil_attachment->set_wrap(w_s, w_t);
        m_depth_stencil_attachment->set_mag_filter(mag_f);
        m_depth_stencil_attachment->set_min_filter(min_f);
    }
    if (m_rbo_id != 0) {
        glDeleteRenderbuffers(1, &m_rbo_id);
        add_depth_stencil_attachment_write_only();
    }
}

bool opengl_framebuffer::is_valid() const {
    bind();
    bool status = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    unbind();
    return status;
}

void opengl_framebuffer::add_color_attachment(texture_api::format t_format) {
    bind();

    ref<texture2d_api> tex = texture2d_api::create_texture2d_api(t_format, m_width, m_height);
    tex->set_min_filter(texture_api::filter::LINEAR);
    tex->set_mag_filter(texture_api::filter::LINEAR);

    m_color_attachments.push_back(tex);

    tex->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_color_attachments.size() - 1, GL_TEXTURE_2D, tex->get_texture_id(), 0);

    // set draw buffers
    GLenum attachmets[m_color_attachments.size()];
    for (int i = 0; i < m_color_attachments.size(); i++) {
        attachmets[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    glDrawBuffers(m_color_attachments.size(), attachmets);

    unbind();
}

void opengl_framebuffer::add_depth_attachment() {
    bind();

    m_depth_attachment = texture2d_api::create_texture2d_api(texture_api::format::DEPTH, m_width, m_height);
    m_depth_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_depth_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_depth_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_attachment->get_texture_id(), 0);

    unbind();
}

void opengl_framebuffer::add_stencil_attachment() {
    bind();

    m_stencil_attachment = texture2d_api::create_texture2d_api(texture_api::format::STENCIL, m_width, m_height);
    m_stencil_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_stencil_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_stencil_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_stencil_attachment->get_texture_id(), 0);
    
    unbind();
}

void opengl_framebuffer::add_depth_stencil_attachment() {
    bind();

    m_depth_stencil_attachment = texture2d_api::create_texture2d_api(texture_api::format::DEPTH_STENCIL, m_width, m_height);
    m_depth_stencil_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_depth_stencil_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_depth_stencil_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_stencil_attachment->get_texture_id(), 0);

    unbind();
}

void opengl_framebuffer::add_depth_stencil_attachment_write_only() {
    bind();

    glGenRenderbuffers(1, &m_rbo_id);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo_id);

    unbind();
}


}

#endif // USE_OPENGL

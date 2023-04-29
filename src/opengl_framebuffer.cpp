#include <ere/impl/opengl/opengl_framebuffer.hpp>
#include <ere/core/logger.hpp>
#include <ere/api/render_api.hpp>
#include <ere/core/application.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {


ref<framebuffer_api> framebuffer_api::create_framebuffer_api(int t_width, int t_height) {
    return std::make_shared<opengl_framebuffer>(t_width, t_height);
}

ref<framebuffer_api> framebuffer_api::get_default_framebuffer_api() {
    if (s_default_framebuffer == nullptr) {
        s_default_framebuffer = std::make_shared<opengl_framebuffer>(0);
    }

    return s_default_framebuffer;
}

ref<framebuffer_api> framebuffer_api::get_current_framebuffer_api() {
    if (s_current_framebuffer.lock() == nullptr) {
        s_current_framebuffer = get_default_framebuffer_api();
    }

    return s_current_framebuffer.lock();
}

opengl_framebuffer::opengl_framebuffer(int t_width, int t_height) {
    m_width = t_width;
    m_height = t_height;
    m_viewport = glm::vec2(t_width, t_height);

    glGenFramebuffers(1, &m_id);
}

opengl_framebuffer::opengl_framebuffer(int t_id) {
    m_id = t_id;
}

opengl_framebuffer::~opengl_framebuffer() {
    if (m_id != 0) {
        glDeleteFramebuffers(1, &m_id);
        if (m_rbo_id != 0) {
            glDeleteRenderbuffers(1, &m_rbo_id);
        }
    }
}

void opengl_framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    render_api::set_viewport(m_viewport);

    s_current_framebuffer = shared_from_this();
}

void opengl_framebuffer::unbind() const {
    if (m_id != 0) {
        get_default_framebuffer_api()->bind();
    }
}

void opengl_framebuffer::disable_color_attachment() {
    auto prev = get_current_framebuffer_api();
    bind();
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    prev->bind();
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

bool opengl_framebuffer::is_valid() {
    auto prev = get_current_framebuffer_api();
    bind();
    bool status = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    prev->bind();
    return status;
}

void opengl_framebuffer::add_color_attachment(texture_api::format t_format) {
    auto prev = get_current_framebuffer_api();
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

    prev->bind();
}

void opengl_framebuffer::add_depth_attachment() {
    auto prev = get_current_framebuffer_api();
    bind();

    m_depth_attachment = texture2d_api::create_texture2d_api(texture_api::format::DEPTH, m_width, m_height);
    m_depth_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_depth_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_depth_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_attachment->get_texture_id(), 0);

    prev->bind();
}

void opengl_framebuffer::add_stencil_attachment() {
    auto prev = get_current_framebuffer_api();
    bind();

    m_stencil_attachment = texture2d_api::create_texture2d_api(texture_api::format::STENCIL, m_width, m_height);
    m_stencil_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_stencil_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_stencil_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_stencil_attachment->get_texture_id(), 0);
    
    prev->bind();
}

void opengl_framebuffer::add_depth_stencil_attachment() {
    auto prev = get_current_framebuffer_api();
    bind();

    m_depth_stencil_attachment = texture2d_api::create_texture2d_api(texture_api::format::DEPTH_STENCIL, m_width, m_height);
    m_depth_stencil_attachment->set_min_filter(texture_api::filter::LINEAR);
    m_depth_stencil_attachment->set_mag_filter(texture_api::filter::LINEAR);

    m_depth_stencil_attachment->bind(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depth_stencil_attachment->get_texture_id(), 0);

    prev->bind();
}

void opengl_framebuffer::add_depth_stencil_attachment_write_only() {
    auto prev = get_current_framebuffer_api();
    bind();

    glGenRenderbuffers(1, &m_rbo_id);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_id);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo_id);

    prev->bind();
}

void opengl_framebuffer::set_viewport(glm::vec2 t_size) {
    m_viewport = t_size;

    if (get_current_framebuffer_api() == shared_from_this()) {
        render_api::set_viewport(m_viewport);
    }
}
glm::vec2 opengl_framebuffer::get_viewport() const {
    return m_viewport;
}


}

#endif // USE_OPENGL

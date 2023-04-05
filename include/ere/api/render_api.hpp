#ifndef __ERE_RENDER_API_HPP__
#define __ERE_RENDER_API_HPP__

#include <ere/core/core.hpp>
#include <glm/glm.hpp>

namespace ere {

class render_api {
public:

    static ref<render_api> get_renderer();
    inline static void init() { get_renderer()->init_impl(); }
    inline static void set_viewport(const glm::vec2& t_size) { get_renderer()->set_viewport_impl(t_size); }
    inline static void clear_color(const glm::vec4& t_color) { get_renderer()->clear_color_impl(t_color); }
    inline static void clear_buffer() { get_renderer()->clear_buffer_impl(); }
    inline static void pre_window_setup() { get_renderer()->pre_window_setup_impl(); }

private:

    virtual void init_impl() = 0;
    virtual void set_viewport_impl(const glm::vec2& t_size) = 0;
    virtual void clear_color_impl(const glm::vec4& t_color) = 0;
    virtual void clear_buffer_impl() = 0;
    virtual void pre_window_setup_impl() = 0;

};

}

#endif // __ERE_RENDER_API_HPP__

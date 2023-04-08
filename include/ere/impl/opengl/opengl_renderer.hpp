#ifndef __ERE_OPENGL_RENDERER_HPP__
#define __ERE_OPENGL_RENDERER_HPP__

#include <ere/ere_config.hpp>
#include <ere/api/render_api.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>

namespace ere {

class opengl_renderer : public render_api {
public:

    virtual void init_impl() override;
    virtual void set_viewport_impl(const glm::vec2& t_size) override;
    virtual void clear_color_impl(const glm::vec4& t_color) override;
    virtual void clear_buffer_impl() override;
    virtual void enable_wireframe_impl() override;
    virtual void disable_wireframe_impl() override;
    virtual void pre_window_setup_impl() override;
    virtual void draw_indexed_impl(const ref<vertex_array_api>& t_vao) override;
    virtual void draw_arrays_impl(const ref<vertex_array_api>& t_vao, int t_vertex_count) override;

};

}

#endif

#endif // __ERE_OPENGL_RENDERER_HPP__

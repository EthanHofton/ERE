#ifndef __ERE_RENDER_API_HPP__
#define __ERE_RENDER_API_HPP__

#include <ere/core/core.hpp>
#include <glm/glm.hpp>
#include <util/timer.hpp>

#include "vertex_array_api.hpp"
#include "shader_api.hpp"
#include "texture_api.hpp"
#include "projection_api.hpp"

namespace ere {

class render_api {
private:

    static glm::mat4 s_projection_matrix;
    static glm::mat4 s_view_matrix;
    static util::raii_timer s_timer;

public:

    virtual ~render_api() = default;

    static ref<render_api> get_renderer();
    inline static void init() { get_renderer()->init_impl(); }
    inline static void set_viewport(const glm::vec2& t_size) { get_renderer()->set_viewport_impl(t_size); }
    inline static void clear_color(const glm::vec4& t_color) { get_renderer()->clear_color_impl(t_color); }
    inline static void clear_buffer() { get_renderer()->clear_buffer_impl(); }
    inline static void pre_window_setup() { get_renderer()->pre_window_setup_impl(); }
    inline static void draw_indexed(const ref<vertex_array_api>& t_vao, const ref<shader_api>& t_shader) {
        t_shader->bind(); 
        set_uniforms(t_shader);
        get_renderer()->draw_indexed_impl(t_vao); 
        t_shader->unbind(); 
    }
    inline static void draw_arrays(const ref<vertex_array_api>& t_vao, const ref<shader_api>& t_shader, int t_vertex_count) { 
        t_shader->bind(); 
        set_uniforms(t_shader);
        get_renderer()->draw_arrays_impl(t_vao, t_vertex_count); 
        t_shader->unbind(); 
    }

    inline static void draw_indexed_textured(const ref<vertex_array_api>& t_vao, const ref<shader_api>& t_shader, const std::vector<ref<texture_api>>& t_texture) {
        t_shader->bind();
        set_uniforms(t_shader);
        set_uniform_textures(t_shader, t_texture);
        get_renderer()->draw_indexed_impl(t_vao);
        unbind_textures(t_texture);
        t_shader->unbind();
    }

    inline static void draw_arrays_textured(const ref<vertex_array_api>& t_vao, const ref<shader_api>& t_shader, int t_vertex_count, const std::vector<ref<texture_api>>& t_texture) {
        t_shader->bind();
        set_uniforms(t_shader);
        set_uniform_textures(t_shader, t_texture);
        get_renderer()->draw_arrays_impl(t_vao, t_vertex_count);
        unbind_textures(t_texture);
        t_shader->unbind();
    }

    inline static void set_projection_matrix(const glm::mat4& t_projection_matrix) { s_projection_matrix = t_projection_matrix; }
    inline static void set_projection_matrix(const ref<projection_api>& t_projection) { s_projection_matrix = t_projection->get_projection_matrix(); }
    inline static void set_view_matrix(const glm::mat4& t_view_matrix) { s_view_matrix = t_view_matrix; }
    // TODO: implement camera_api
    // inline static void set_view_matrix(const ref<camera_api>& t_camera) { s_view_matrix = t_camera->get_view_matrix(); }

private:

    inline static void set_uniforms(const ref<shader_api>& t_shader) {
        t_shader->set_uniform_mat4f("u_projection", s_projection_matrix);
        t_shader->set_uniform_mat4f("u_view", s_view_matrix);
        t_shader->set_uniform_1f("u_time", (float)s_timer.getTime() * 1e-9);
    }

    inline static void set_uniform_textures(const ref<shader_api>& t_shader, const std::vector<ref<texture_api>>& t_textures) {
        for (int i = 0; i < t_textures.size(); i++) {
            t_textures[i]->bind(i);
            t_shader->set_uniform_1i(t_textures[i]->get_uniform_name(), i);
        }
    }

    inline static void unbind_textures(const std::vector<ref<texture_api>>& t_textures) {
        for (int i = 0; i < t_textures.size(); i++) {
            t_textures[i]->unbind();
        }
    }

private:

    virtual void init_impl() = 0;
    virtual void set_viewport_impl(const glm::vec2& t_size) = 0;
    virtual void clear_color_impl(const glm::vec4& t_color) = 0;
    virtual void clear_buffer_impl() = 0;
    virtual void pre_window_setup_impl() = 0;
    virtual void draw_indexed_impl(const ref<vertex_array_api>& t_vao) = 0;
    virtual void draw_arrays_impl(const ref<vertex_array_api>& t_vao, int t_vertex_count) = 0;

};

}

#endif // __ERE_RENDER_API_HPP__

#ifndef __ERE_RENDER_API_HPP__
#define __ERE_RENDER_API_HPP__

#include <ere/core/core.hpp>
#include <glm/glm.hpp>
#include <util/timer.hpp>

#include "vertex_array_api.hpp"
#include "shader_api.hpp"
#include "texture_api.hpp"
#include "camera_api.hpp"

namespace ere {

class render_api {
private:

    static ref<camera_api> s_camera;
    static util::raii_timer s_timer;

public:

    enum class culling_face {
        FRONT,
        BACK,
        FRONT_AND_BACK
    };

    enum class culling_direction {
        CLOCKWISE,
        COUNTER_CLOCKWISE
    };

    virtual ~render_api() = default;

    static ref<render_api> get_renderer();
    inline static void init() { get_renderer()->init_impl(); }

    inline static void set_viewport(const glm::vec2& t_size) { get_renderer()->set_viewport_impl(t_size); }

    inline static void clear_color(const glm::vec4& t_color) { get_renderer()->clear_color_impl(t_color); }

    inline static void clear_buffers() { get_renderer()->clear_buffers_impl(); }
    inline static void clear_color_buffer() { get_renderer()->clear_color_buffer_impl(); }
    inline static void clear_depth_buffer() { get_renderer()->clear_depth_buffer_impl(); }
    inline static void clear_stencil_buffer() { get_renderer()->clear_stencil_buffer_impl(); }

    inline static void enable_wireframe() { get_renderer()->enable_wireframe_impl(); }
    inline static void disable_wireframe() { get_renderer()->disable_wireframe_impl(); }

    inline static void enable_depth_testing() { get_renderer()->enable_depth_testing_impl(); }
    inline static void enable_depth_test_write() { get_renderer()->enable_depth_test_write_impl(); }
    inline static void disable_depth_testing() { get_renderer()->disable_depth_testing_impl(); }
    inline static void disable_depth_test_write() { get_renderer()->disable_depth_test_write_impl(); }

    inline static void enable_blending() { get_renderer()->enable_blending_impl(); }
    inline static void disable_blending() { get_renderer()->disable_blending_impl(); }

    inline static void enable_culling(const culling_face& t_face, const culling_direction& t_direction) { get_renderer()->enable_culling_impl(t_face, t_direction); }
    inline static void disable_culling() { get_renderer()->disable_culling_impl(); }

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

    inline static void set_camera(const ref<camera_api>& t_camera) { s_camera = t_camera; }

private:

    inline static void set_uniforms(const ref<shader_api>& t_shader) {
        t_shader->set_uniform_mat4f("u_projection", s_camera->get_projection_matrix());
        t_shader->set_uniform_mat4f("u_view", s_camera->get_view_matrix());
        t_shader->set_uniform_3f("u_cam_pos", s_camera->get_position());
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

    virtual void clear_buffers_impl() = 0;
    virtual void clear_color_buffer_impl() = 0;
    virtual void clear_depth_buffer_impl() = 0;
    virtual void clear_stencil_buffer_impl() = 0;

    virtual void enable_wireframe_impl() = 0;
    virtual void disable_wireframe_impl() = 0;

    virtual void enable_depth_testing_impl() = 0;
    virtual void enable_depth_test_write_impl() = 0;
    virtual void disable_depth_testing_impl() = 0;
    virtual void disable_depth_test_write_impl() = 0;

    virtual void enable_blending_impl() = 0;
    virtual void disable_blending_impl() = 0;

    virtual void enable_culling_impl(const culling_face& t_face, const culling_direction& t_direction) = 0;
    virtual void disable_culling_impl() = 0;

    virtual void pre_window_setup_impl() = 0;

    virtual void draw_indexed_impl(const ref<vertex_array_api>& t_vao) = 0;
    virtual void draw_arrays_impl(const ref<vertex_array_api>& t_vao, int t_vertex_count) = 0;

};

}

#endif // __ERE_RENDER_API_HPP__

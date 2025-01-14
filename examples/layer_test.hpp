#ifndef __LAYER_TEST_HPP__
#define __LAYER_TEST_HPP__

#include <ere/core/layer.hpp>
#include <ere/core/application.hpp>
#include <ere/mappings/key_map.hpp>
#include <ere/api/render_api.hpp>
#include <ere/api/texture_api.hpp>
#include <ere/core/camera_3d.hpp>
#include <ere/api/vertex_array_api.hpp>
#include <ere/api/vertex_buffer_api.hpp>
#include <ere/api/index_buffer_api.hpp>
#include <ere/api/shader_api.hpp>

#include <imgui.h>

namespace ere {

class l1 : public layer {
public:

    bool on_key_pressed(key_pressed_event& e) override {
        if (e.get_key_code() == ERE_KEY_C) {
            application::get_application()->set_background_color({0.1f, 1.f, 0.1f, 1.0f});
        }
    
        m_camera->on_key_pressed(e);

        return true;
    }

    bool on_mouse_moved(mouse_moved_event& e) override {
        m_camera->on_mouse_moved(e);
        return true;
    }

    bool on_mouse_scrolled(mouse_scrolled_event& e) override {
        m_camera->on_mouse_scrolled(e);
        return true;
    }

    bool on_attach(attach_event& e) override {
        // create the camera
        m_camera = createRef<camera_3d>();
        render_api::set_camera(m_camera);

        // create the texture
        m_container_texture = texture_api::create_texture_api("assets/images/container.jpg");
        m_container_texture->set_uniform_name("uContainer");

        // create the shader
        m_shader = shader_api::create_shader_api_from_file("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

        // create the triangle data
        m_square_pos = {
           -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f,  0.5f, 0.f,
           -0.5f,  0.5f, 0.f
        };

        m_square_colors = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f
        };

        m_square_uv = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };

        m_square_indices = {
            0, 1, 2,
            2, 3, 0
        };

        // create the vertex array
        m_vao = vertex_array_api::create_vertex_array_api();

        // create the vertex buffer
        m_vbo_pos = vertex_buffer_api::create_vertex_buffer_api(m_square_pos.data(), m_square_pos.size() * sizeof(float));

        // create the vertex buffer layout
        buffer_layout layout = {
            { "aPos", buffer_layout::shader_type::float_3, false }
        };

        // set the layout
        m_vbo_pos->set_layout(layout);
        m_vao->add_vertex_buffer(m_vbo_pos);

        m_vbo_color = vertex_buffer_api::create_vertex_buffer_api(m_square_colors.data(), m_square_colors.size() * sizeof(float));

        // create the vertex buffer layout
        buffer_layout layout2 = {
            { "aColor", buffer_layout::shader_type::float_3, false }
        };

        // set the layout
        m_vbo_color->set_layout(layout2);

        // add the vertex buffer to the vertex array
        m_vao->add_vertex_buffer(m_vbo_color);

        m_vbo_uv = vertex_buffer_api::create_vertex_buffer_api(m_square_uv.data(), m_square_uv.size() * sizeof(float));

        // create the vertex buffer layout
        buffer_layout layout3 = {
            { "aUv", buffer_layout::shader_type::float_2, false }
        };

        // set the layout
        m_vbo_uv->set_layout(layout3);

        // add the vertex buffer to the vertex array
        m_vao->add_vertex_buffer(m_vbo_uv);

        // create the index buffer
        m_ibo = index_buffer_api::create_index_buffer_api(m_square_indices.data(), m_square_indices.size() * sizeof(uint32_t));
        m_vao->set_index_buffer(m_ibo);

        return false;
    }

    bool on_update(update_event& e) override {
        m_camera->on_update(e);

        render_api::draw_indexed_textured(m_vao, m_shader, {m_container_texture});

        return false;
    }

    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowDemoWindow();
        return false;
    }

private:

    ref<shader_api> m_shader;

    ref<texture_api> m_container_texture;

    ref<vertex_array_api> m_vao;
    ref<vertex_buffer_api> m_vbo_pos;
    ref<vertex_buffer_api> m_vbo_color;
    ref<vertex_buffer_api> m_vbo_uv;

    ref<index_buffer_api> m_ibo;

    std::vector<float> m_square_pos;
    std::vector<float> m_square_colors;
    std::vector<float> m_square_uv;
    std::vector<uint32_t> m_square_indices;

    ref<camera_3d> m_camera;

    util::raii_timer m_timer;
};


}

#endif

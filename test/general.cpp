#include <ere/core/entry_point.hpp>
#include <ere/core/layer.hpp>
#include <ere/mappings/key_map.hpp>
#include <imgui.h>
#include <ere/api/render_api.hpp>

#include <iostream>

namespace ere {

class l1 : public layer {
public:

    bool on_key_pressed(key_pressed_event& e) override {
        if (e.get_key_code() == ERE_KEY_C) {
            application::get_application()->set_background_color({0.1f, 1.f, 0.1f, 1.0f});
        }
        return true;
    }

    bool on_attach(attach_event& e) override {
        // create the shader
        m_shader = shader_api::create_shader_api_from_file("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

        // create the triangle data
        m_square_pos = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };

        m_square_colors = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f
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

        // create the index buffer
        m_ibo = index_buffer_api::create_index_buffer_api(m_square_indices.data(), m_square_indices.size() * sizeof(uint32_t));
        m_vao->set_index_buffer(m_ibo);

        return false;
    }

    bool on_update(update_event& e) override {

        render_api::draw_indexed(m_vao, m_shader);

        return false;
    }

    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowDemoWindow();
        return false;
    }

private:

    ref<shader_api> m_shader;
    ref<vertex_array_api> m_vao;
    ref<vertex_buffer_api> m_vbo_pos;
    ref<vertex_buffer_api> m_vbo_color;
    ref<index_buffer_api> m_ibo;

    std::vector<float> m_square_pos;
    std::vector<float> m_square_colors;
    std::vector<uint32_t> m_square_indices;
};

ref<ere::application> ere_create_application() {
    ref<application> app = application::get_application();

    app->push_layer(createRef<l1>());

    app->set_background_color({0.1f, 0.1f, 0.1f, 1.0f});
    app->set_fps(120.0);
    app->set_window_title("Ere Engine TEST CHANGE");
    app->vsync(false);
    

    return app;
}

}

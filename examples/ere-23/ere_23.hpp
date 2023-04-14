#ifndef __ERE_23_HPP__
#define __E 

#include "cube.hpp"

#include <ere/core/application.hpp>
#include <ere/core/camera_3d.hpp>
#include <ere/core/layer.hpp>
#include <ere/api/render_api.hpp>
#include <ere/api/framebuffer_api.hpp>
#include <ere/api/cubemap_api.hpp>

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

#include <util/random.hpp>
#include <util/math.hpp>

namespace ere {

class ere_23 : public layer {
public:

    bool on_attach(attach_event& e) override {
        m_camera = createRef<camera_3d>();
        render_api::set_camera(m_camera);
        m_camera->set_far(10000.0f);
        m_camera->set_move_speed(100.0f);

        m_cube = createRef<cube>(glm::vec3(1, 1, 1));
        m_cube_shader = shader_api::create_shader_api_from_file("assets/shaders/ere-23/vert.glsl", "assets/shaders/ere-23/frag.glsl");

        gen_positions();

        m_instance_vbo = vertex_buffer_api::create_vertex_buffer_api(positions.data(), positions.size() * sizeof(glm::vec3));
        m_instance_vbo->set_layout({
            { "a_position", buffer_layout::shader_type::float_3, 1, false },
        });

        m_cube->m_vao->add_vertex_buffer(m_instance_vbo);

        render_api::enable_culling(render_api::culling_face::BACK, render_api::culling_direction::COUNTER_CLOCKWISE);

        return true;
    }

    bool on_update(update_event& e) override {
        m_camera->on_update(e);

        render_api::draw_indexed_instanced(m_cube->m_vao, m_cube_shader, positions.size());

        return true;
    }

    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowMetricsWindow();
        return true;
    }

    bool on_key_pressed(key_pressed_event& e) override {
        m_camera->on_key_pressed(e);
        if (e.get_key_code() == ERE_KEY_X) {
            m_wireframe = !m_wireframe;
            (m_wireframe) ? render_api::enable_wireframe() : render_api::disable_wireframe();
        }
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

    bool on_window_resized(window_resized_event& e) override {
        m_camera->on_window_resized(e);
        return true;
    }

    bool on_window_framebuffer_resized(window_framebuffer_resized_event& e) override {
        return true;
    }

private:

    void gen_positions() {
        glm::vec3 center = {0, 0, 0};
        float inner_radius = 100.0f;
        float outer_radius = 10000.0f;

        util::prng rng;

        for (int i = 0; i < 1000000; i++) {
            float r = rng.rand(inner_radius, outer_radius);
            float theta = rng.rand(0.0f, 2.0f * util::PI);
            float phi = rng.rand(0.0f, util::PI);

            float x = r * sin(phi) * cos(theta);
            float y = r * sin(phi) * sin(theta);
            float z = r * cos(phi);

            positions.push_back({x, y, z});
        }
    }

private:

    ref<framebuffer_api> m_framebuffer;

    // base elements required for rendering
    ref<camera_3d> m_camera;
    bool m_wireframe = false;

    ref<cube> m_cube;
    ref<shader_api> m_cube_shader;

    std::vector<glm::vec3> positions;
    ref<vertex_buffer_api> m_instance_vbo;
};

}

#endif

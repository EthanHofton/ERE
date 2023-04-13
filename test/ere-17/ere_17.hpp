#ifndef __ERE_21_HPP__
#define __ERE_21_HPP__

#include "../ere-21/cube.hpp"
#include "../ere-21/sphere.hpp"
#include "../ere-21/light_scene.hpp"

#include <ere/core/application.hpp>
#include <ere/core/camera_3d.hpp>
#include <ere/core/layer.hpp>
#include <ere/api/render_api.hpp>
#include <ere/api/framebuffer_api.hpp>

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace ere {

class ere_17 : public layer {
public:

    bool on_attach(attach_event& e) override {
        m_camera = createRef<camera_3d>();
        render_api::set_camera(m_camera);

        m_light_scene = createRef<light_scene>();
        m_light_source_cube_shader = shader_api::create_shader_api_from_file("assets/shaders/ere-21/vertex.glsl", "assets/shaders/ere-21/fragment.glsl");

        m_light_source_cubes = createRef<cube>(cube{
            glm::vec3(.5f, .5f, .5f),
            glm::vec3(0.f, 0.f, 0.f),
        });

        m_cube = createRef<cube>(cube{
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(0.f, 0.f, 0.f),
        });

        m_cube->set_material(material{
            .ambient = glm::vec3(0),
            .diffuse = glm::vec3(0),
            .specular = glm::vec3(0),
            .shininess = 8.f,
            .diffuse_texture = texture2d_api::create_texture2d_api("assets/images/container2.png"),
            .specular_texture = texture2d_api::create_texture2d_api("assets/images/container2_specular.png"),
        });

        m_cube_positions = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        m_spot_light = createRef<spot_light>(spot_light{
            .position = m_camera->get_position(),
            .direction = m_camera->get_camera_front(),
            .cut_off = glm::radians(12.5f),
            .outer_cut_off = glm::radians(15.f),
            .ambient = glm::vec3(0.1f, 0.1f, 0.1f),
            .diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
            .specular = glm::vec3(1.f, 1.f, 1.f),
            .constant = 1.f,
            .linear = 0.09f,
            .quadratic = 0.032f,
        });
        m_light_scene->add_spot_light(m_spot_light);

        m_framebuffer = framebuffer_api::create_framebuffer_api(application::get_application()->get_window_size().x, application::get_application()->get_window_size().y);
        m_framebuffer->add_color_attachment(texture_api::format::RGB16F);
        m_framebuffer->add_color_attachment(texture_api::format::RGB16F);
        m_framebuffer->add_depth_attachment();
        m_framebuffer->get_color_attachemt(0)->set_uniform_name("color_buffer");
        m_framebuffer->get_color_attachemt(1)->set_uniform_name("color_buffer");

        
        // the vec3 positions of the quad
        m_quad_vertices = {
            // positions        // texture Coords
            glm::vec3(-1.0f,  1.0f, 0.0f),
            glm::vec3(-1.0f, -1.0f, 0.0f),
            glm::vec3( 1.0f, -1.0f, 0.0f),

            glm::vec3(-1.0f,  1.0f, 0.0f),
            glm::vec3( 1.0f, -1.0f, 0.0f),
            glm::vec3( 1.0f,  1.0f, 0.0f),
        };

        m_quad_tex_coords = {
            glm::vec2(0.0f, 1.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),

            glm::vec2(0.0f, 1.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
        };

        m_quad_indices = {
            0, 1, 2,
            3, 4, 5,
        };

        m_quad_vao = vertex_array_api::create_vertex_array_api();
        m_quad_pos_vbo = vertex_buffer_api::create_vertex_buffer_api(&m_quad_vertices[0], m_quad_vertices.size() * sizeof(glm::vec3));
        m_quad_pos_vbo->set_layout({
            { "a_pos", buffer_layout::shader_type::float_3, false },
        });

        m_quad_tex_vbo = vertex_buffer_api::create_vertex_buffer_api(&m_quad_tex_coords[0], m_quad_tex_coords.size() * sizeof(glm::vec2));
        m_quad_tex_vbo->set_layout({
            { "a_tex_coord", buffer_layout::shader_type::float_2, false },
        });

        m_quad_ibo = index_buffer_api::create_index_buffer_api(&m_quad_indices[0], m_quad_indices.size() * sizeof(uint32_t));

        m_quad_vao->add_vertex_buffer(m_quad_pos_vbo);
        m_quad_vao->add_vertex_buffer(m_quad_tex_vbo);

        m_quad_vao->set_index_buffer(m_quad_ibo);

        m_quad_shader = shader_api::create_shader_api_from_file("assets/shaders/ere-17/quad_vert.glsl", "assets/shaders/ere-17/quad_frag.glsl");

        return true;
    }

    bool on_update(update_event& e) override {
        m_camera->on_update(e);

        m_framebuffer->bind();
        render_api::clear_buffers();

        render_scene();

        m_framebuffer->unbind();

        render_api::draw_indexed_textured(m_quad_vao, m_quad_shader, { m_framebuffer->get_color_attachemt(index) });

        return true;
    }

    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowMetricsWindow();

        // shop a window for each directional light source
        for (int i = 0; i < m_light_scene->get_directional_lights().size(); ++i) {
            auto& light = m_light_scene->get_directional_lights()[i];
            ImGui::Begin(("Directional Light " + std::to_string(i)).c_str());
            ImGui::DragFloat3("Direction", glm::value_ptr(light->direction), 0.1f);
            ImGui::ColorEdit3("Ambient", glm::value_ptr(light->ambient));
            ImGui::ColorEdit3("Diffuse", glm::value_ptr(light->diffuse));
            ImGui::ColorEdit3("Specular", glm::value_ptr(light->specular));
            ImGui::End();
        }

        // show a window for each light source
        for (int i = 0; i < m_light_scene->get_lights().size(); ++i) {
            auto& light = m_light_scene->get_lights()[i];
            ImGui::Begin(("Light " + std::to_string(i)).c_str());
            ImGui::DragFloat3("Direction", glm::value_ptr(light->position), 0.1f);
            ImGui::ColorEdit3("Ambient", glm::value_ptr(light->ambient));
            ImGui::ColorEdit3("Diffuse", glm::value_ptr(light->diffuse));
            ImGui::ColorEdit3("Specular", glm::value_ptr(light->specular));
            ImGui::End();
        }

        // show a window for each point light source
        for (int i = 0; i < m_light_scene->get_point_lights().size(); ++i) {
            auto& light = m_light_scene->get_point_lights()[i];
            ImGui::Begin(("Point Light " + std::to_string(i)).c_str());
            ImGui::DragFloat3("Position", glm::value_ptr(light->position), 0.1f);
            ImGui::ColorEdit3("Ambient", glm::value_ptr(light->ambient));
            ImGui::ColorEdit3("Diffuse", glm::value_ptr(light->diffuse));
            ImGui::ColorEdit3("Specular", glm::value_ptr(light->specular));
            ImGui::DragFloat("Constant", &light->constant, 0.1f);
            ImGui::DragFloat("Linear", &light->linear, 0.1f);
            ImGui::DragFloat("Quadratic", &light->quadratic, 0.1f);
            ImGui::End();
        }

        // show a window for each spot light source
        for (int i = 0; i < m_light_scene->get_spot_lights().size(); ++i) {
            auto& light = m_light_scene->get_spot_lights()[i];
            ImGui::Begin(("Spot Light " + std::to_string(i)).c_str());
            ImGui::DragFloat3("Position", glm::value_ptr(light->position), 0.1f);
            ImGui::DragFloat3("Direction", glm::value_ptr(light->direction), 0.1f);
            ImGui::ColorEdit3("Ambient", glm::value_ptr(light->ambient));
            ImGui::ColorEdit3("Diffuse", glm::value_ptr(light->diffuse));
            ImGui::ColorEdit3("Specular", glm::value_ptr(light->specular));
            ImGui::DragFloat("Constant", &light->constant, 0.1f);
            ImGui::DragFloat("Linear", &light->linear, 0.1f);
            ImGui::DragFloat("Quadratic", &light->quadratic, 0.1f);
            ImGui::SliderAngle("CutOff", &light->cut_off, 0, 360);
            ImGui::SliderAngle("OuterCutOff", &light->outer_cut_off, 0, 360);
            ImGui::End();
        }

        // window to add a new light source
        ImGui::Begin("Add Light");
        // light source type selection
        static int light_type = 0;
        ImGui::RadioButton("Simple", &light_type, 0);
        ImGui::RadioButton("Directional", &light_type, 1);
        ImGui::RadioButton("Point", &light_type, 2);
        ImGui::RadioButton("Spot", &light_type, 3);

        // light source position/direction
        static glm::vec3 light_pos = glm::vec3(0.0f, 0.0f, 0.0f);
        if (light_type == 0 || light_type == 2 || light_type == 3) {
            ImGui::DragFloat3("Position", glm::value_ptr(light_pos), 0.1f);
        } else {
            ImGui::DragFloat3("Direction", glm::value_ptr(light_pos), 0.1f);
        }

        // light source color
        static glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        static glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        static glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
        ImGui::ColorEdit3("Ambient", glm::value_ptr(ambient));
        ImGui::ColorEdit3("Diffuse", glm::value_ptr(diffuse));
        ImGui::ColorEdit3("Specular", glm::value_ptr(specular));

        // light source attenuation
        static float constant = 1.0f;
        static float linear = 0.09f;
        static float quadratic = 0.032f;
        if (light_type == 2 || light_type == 3) {
            ImGui::DragFloat("Constant", &constant, 0.1f);
            ImGui::DragFloat("Linear", &linear, 0.1f);
            ImGui::DragFloat("Quadratic", &quadratic, 0.1f);
        }

        // light source cut off
        static float cut_off = 12.5f;
        static float outer_cut_off = 17.5f;
        if (light_type == 3) {
            ImGui::SliderAngle("CutOff", &cut_off, 0, 360);
            ImGui::SliderAngle("OuterCutOff", &outer_cut_off, 0, 360);
        }

        static glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
        if (light_type == 3) {
            ImGui::DragFloat3("Direction", glm::value_ptr(direction), 0.1f);
        }

        // add light source button
        if (ImGui::Button("Add Light")) {
            switch (light_type) {
                case 0:
                    m_light_scene->add_light(createRef<light>(light{light_pos, ambient, diffuse, specular}));
                    break;
                case 1:
                    m_light_scene->add_directional_light(createRef<directional_light>(directional_light{light_pos, ambient, diffuse, specular}));
                    break;
                case 2:
                    m_light_scene->add_point_light(createRef<point_light>(point_light{light_pos, ambient, diffuse, specular, constant, linear, quadratic}));
                    break;
                case 3:
                    m_light_scene->add_spot_light(createRef<spot_light>(spot_light{light_pos, direction, cut_off, outer_cut_off, ambient, diffuse, specular, constant, linear, quadratic}));
                    break;
            }
        }

        ImGui::End();

        ImGui::Begin("Framebuffer Color Buffer");
        ImGui::InputInt("Color Buffer Index", &index, 0);
        ImGui::End();

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
        m_framebuffer->resize(e.get_window_framebuffer_size().x, e.get_window_framebuffer_size().y);
        return true;
    }

private:

    void render_scene() {
        m_spot_light->position = m_camera->get_position();
        m_spot_light->direction = m_camera->get_camera_front();

        for (int i = 0; i < 10; i++) {
            m_cube->set_pos(m_cube_positions[i]);
            m_cube->set_rotation(glm::radians(20.f * i));
            m_cube->set_rotation_axis(glm::vec3(1.0f, 0.3f, 0.5f));
            m_light_scene->draw(m_cube);
        }

        for (auto& light : m_light_scene->get_lights()) {
            m_light_source_cubes->set_pos(light->position);
            m_light_source_cubes->set_material(material{
                light->ambient,
                light->diffuse,
                light->specular,
                32.f,
            });
            m_light_scene->draw(m_light_source_cubes);
        }

        for (auto& light : m_light_scene->get_point_lights()) {
            m_light_source_cubes->set_pos(light->position);
            m_light_source_cubes->set_material(material{
                light->ambient,
                light->diffuse,
                light->specular,
                32.f,
            });
            m_light_scene->draw(m_light_source_cubes);
        }

        for (auto& light : m_light_scene->get_spot_lights()) {
            if (light != m_spot_light) {
                m_light_source_cubes->set_pos(light->position);
                m_light_source_cubes->set_material(material{
                    light->ambient,
                    light->diffuse,
                    light->specular,
                    32.f,
                });
                m_light_scene->draw(m_light_source_cubes);
            }
        }
    }

private:

    ref<framebuffer_api> m_framebuffer;

    // base elements required for rendering
    ref<camera_3d> m_camera;
    bool m_wireframe = false;

    // light scene
    ref<light_scene> m_light_scene;
    // std::vector<ref<shape>> m_shapes;
    ref<cube> m_cube;
    ref<cube> m_light_source_cubes;
    ref<shader_api> m_light_source_cube_shader;
    std::vector<glm::vec3> m_cube_positions;


    std::vector<glm::vec3> m_quad_vertices;
    std::vector<glm::vec2> m_quad_tex_coords;
    std::vector<unsigned int> m_quad_indices;
    ref<vertex_array_api> m_quad_vao;
    ref<vertex_buffer_api> m_quad_pos_vbo;
    ref<vertex_buffer_api> m_quad_tex_vbo;
    ref<index_buffer_api> m_quad_ibo;
    ref<shader_api> m_quad_shader;

    ref<spot_light> m_spot_light;

    // test
    int index = 0;

};

}

#endif

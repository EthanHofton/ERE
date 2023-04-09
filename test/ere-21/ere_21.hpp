#ifndef __ERE_21_HPP__
#define __ERE_21_HPP__

#include "cube.hpp"
#include "sphere.hpp"
#include "light_scene.hpp"

#include <ere/core/camera_3d.hpp>
#include <ere/core/layer.hpp>
#include <ere/api/render_api.hpp>

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

namespace ere {

class ere_21 : public layer {
public:

    bool on_attach(attach_event& e) override {
        m_camera = createRef<camera_3d>();
        render_api::set_camera(m_camera);

        m_light_scene = createRef<light_scene>();

        m_shapes.push_back(createRef<cube>(glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f)));
        m_shapes.push_back(createRef<sphere>(1.f, glm::vec3(-2.f, 0.f, 0.f)));

        m_shapes[0]->set_material({
            .ambient = glm::vec3(1.f, 0.5f, 0.31f),
            .diffuse = glm::vec3(1.f, 0.5f, 0.31f),
            .specular = glm::vec3(0.5f, 0.5f, 0.5f),
            .shininess = 32.f,
        });

        m_shapes[1]->set_material({
            .ambient = glm::vec3(1.f, 0.5f, 0.31f),
            .diffuse = glm::vec3(1.f, 0.5f, 0.31f),
            .specular = glm::vec3(0.5f, 0.5f, 0.5f),
            .shininess = 32.f,
        });

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

        return true;
    }

    bool on_update(update_event& e) override {
        m_camera->on_update(e);
        m_spot_light->position = m_camera->get_position();
        m_spot_light->direction = m_camera->get_camera_front();

        for (auto& shape : m_shapes) {
            m_light_scene->draw(shape);
        }

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

private:

    // base elements required for rendering
    ref<camera_3d> m_camera;
    bool m_wireframe = false;

    // light scene
    ref<light_scene> m_light_scene;
    std::vector<ref<shape>> m_shapes;

    ref<spot_light> m_spot_light;

};

}

#endif

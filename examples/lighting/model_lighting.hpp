#ifndef __MODEL_LIGHTING_HPP__
#define __MODEL_LIGHTING_HPP__

#include <ere/core/layer.hpp>
#include <ere/core/core.hpp>
#include <ere/core/camera_3d.hpp>
#include <ere/api/render_api.hpp>

#include <imgui.h>

#include <glm/gtc/type_ptr.hpp>

#include "light_scene.hpp"
#include "model.hpp"

namespace ere {

class model_lighting : public layer {
public:

    bool on_attach(attach_event& e) override {
        m_camera = createRef<camera_3d>();
        m_camera->set_far(1000.0f);
        render_api::set_camera(m_camera);

        m_light_scene = createRef<light_scene>();
        // m_model = createRef<model>("assets/backpack/backpack.obj");
        m_model = createRef<model>("assets/Sponza/sponza.obj", m_light_scene);

        m_spot_light = createRef<spot_light>(spot_light{
            .position = m_camera->get_position(),
            .direction = m_camera->get_camera_front(),
            .cut_off = glm::radians(12.5f),
            .outer_cut_off = glm::radians(15.0f),
            .ambient = glm::vec3(1.0f),
            .diffuse = glm::vec3(1.0f),
            .specular = glm::vec3(1.0f),
            .constant = 1.0f,
            .linear = 0.0014f,
            .quadratic = 0.000007f,
        });

        m_light_scene->add_spot_light(m_spot_light);

        return true;
    }

    bool on_update(update_event& e) override {
        m_camera->on_update(e);

        m_spot_light->position = m_camera->get_position();
        m_spot_light->direction = m_camera->get_camera_front();

        m_model->draw();

        return true;
    }

    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowMetricsWindow();

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

        // camera settings
        ImGui::Begin("Camera");
        static float camera_move_speed = 10.f;
        static float camera_turn_speed = 10.f;
        if (ImGui::DragFloat("Camera Speed", &camera_move_speed, 0.1f)) {
            m_camera->set_move_speed(camera_move_speed);
        }
        if (ImGui::DragFloat("Camera Sensitivity", &camera_turn_speed, 0.1f)) {
            m_camera->set_turn_speed(camera_turn_speed);
        }
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

private:

    // base elements required for rendering
    ref<camera_3d> m_camera;
    bool m_wireframe = false;

    ref<light_scene> m_light_scene;

    ref<spot_light> m_spot_light;

    ref<model> m_model;

};

}


#endif

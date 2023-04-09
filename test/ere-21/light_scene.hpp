#ifndef __LIGHT_SCENE_HPP__
#define __LIGHT_SCENE_HPP__

#include "shape.hpp"
#include "light.hpp"

#include <ere/api/shader_api.hpp>

namespace ere {

class light_scene {
public:

    light_scene() {
        m_shader = shader_api::create_shader_api_from_file("assets/shaders/ere-21/light_vertex.glsl", "assets/shaders/ere-21/light_fragment.glsl");
        // m_shader = shader_api::create_shader_api_from_file("assets/shaders/ere-21/vertex.glsl", "assets/shaders/ere-21/fragment.glsl");
    }

    void draw(ref<shape> t_shape) {
        ref<shader_api> shader = get_shader(t_shape);
        t_shape->draw(shader);
    }

    ref<shader_api> get_shader(ref<shape> t_shape) {
        // set material uniforms
        m_shader->set_uniform_3f("uMaterial.ambient", t_shape->get_material().ambient);
        m_shader->set_uniform_3f("uMaterial.diffuse", t_shape->get_material().diffuse);
        m_shader->set_uniform_3f("uMaterial.specular", t_shape->get_material().specular);
        m_shader->set_uniform_1f("uMaterial.shininess", t_shape->get_material().shininess);

        // set light uniforms
        int direction_lights;
        for (direction_lights = 0; direction_lights < m_directional_lights.size(); direction_lights++) {
            ref<directional_light> light = m_directional_lights[direction_lights];
            m_shader->set_uniform_4f("uDirLights[" + std::to_string(direction_lights) + "].direction", {light->direction.x, light->direction.y, light->direction.z, 0.0f});
            m_shader->set_uniform_3f("uDirLights[" + std::to_string(direction_lights) + "].ambient", light->ambient);
            m_shader->set_uniform_3f("uDirLights[" + std::to_string(direction_lights) + "].diffuse", light->diffuse);
            m_shader->set_uniform_3f("uDirLights[" + std::to_string(direction_lights) + "].specular", light->specular);
        }

        for (int i = 0; i < m_lights.size(); i++,direction_lights++) {
            ref<light> light = m_lights[i];
            m_shader->set_uniform_4f("uDirLights[" + std::to_string(direction_lights) + "].direction", {light->position.x, light->position.y, light->position.z, 1.0f});
            m_shader->set_uniform_3f("uDirLights[" + std::to_string(direction_lights) + "].ambient", light->ambient);
            m_shader->set_uniform_3f("uDirLights[" + std::to_string(direction_lights) + "].diffuse", light->diffuse);
            m_shader->set_uniform_3f("uDirLights[" + std::to_string(direction_lights) + "].specular", light->specular);
        }

        for (int i = 0; i < m_point_lights.size(); i++) {
            ref<point_light> light = m_point_lights[i];
            m_shader->set_uniform_3f("uPointLights[" + std::to_string(i) + "].position", {light->position.x, light->position.y, light->position.z});
            m_shader->set_uniform_3f("uPointLights[" + std::to_string(i) + "].ambient", light->ambient);
            m_shader->set_uniform_3f("uPointLights[" + std::to_string(i) + "].diffuse", light->diffuse);
            m_shader->set_uniform_3f("uPointLights[" + std::to_string(i) + "].specular", light->specular);
            m_shader->set_uniform_1f("uPointLights[" + std::to_string(i) + "].constant", light->constant);
            m_shader->set_uniform_1f("uPointLights[" + std::to_string(i) + "].linear", light->linear);
            m_shader->set_uniform_1f("uPointLights[" + std::to_string(i) + "].quadratic", light->quadratic);
        }

        for (int i = 0; i < m_spot_lights.size(); i++) {
            ref<spot_light> light = m_spot_lights[i];
            m_shader->set_uniform_3f("uSpotLights[" + std::to_string(i) + "].position", {light->position.x, light->position.y, light->position.z});
            m_shader->set_uniform_3f("uSpotLights[" + std::to_string(i) + "].direction", {light->direction.x, light->direction.y, light->direction.z});
            m_shader->set_uniform_3f("uSpotLights[" + std::to_string(i) + "].ambient", light->ambient);
            m_shader->set_uniform_3f("uSpotLights[" + std::to_string(i) + "].diffuse", light->diffuse);
            m_shader->set_uniform_3f("uSpotLights[" + std::to_string(i) + "].specular", light->specular);
            m_shader->set_uniform_1f("uSpotLights[" + std::to_string(i) + "].constant", light->constant);
            m_shader->set_uniform_1f("uSpotLights[" + std::to_string(i) + "].linear", light->linear);
            m_shader->set_uniform_1f("uSpotLights[" + std::to_string(i) + "].quadratic", light->quadratic);
            m_shader->set_uniform_1f("uSpotLights[" + std::to_string(i) + "].cutOff", glm::cos(light->cut_off));
            m_shader->set_uniform_1f("uSpotLights[" + std::to_string(i) + "].outerCutOff", glm::cos(light->outer_cut_off));
        }

        return m_shader;
    }

    void add_light(ref<light> t_light) {
        m_lights.push_back(t_light);
    }
    const std::vector<ref<light>>& get_lights() const { return m_lights; }
    std::vector<ref<light>>& get_lights() { return m_lights; }

    void add_directional_light(ref<directional_light> t_light) {
        m_directional_lights.push_back(t_light);
    }
    const std::vector<ref<directional_light>>& get_directional_lights() const { return m_directional_lights; }
    std::vector<ref<directional_light>>& get_directional_lights() { return m_directional_lights; }

    void add_point_light(ref<point_light> t_light) {
        m_point_lights.push_back(t_light);
    }
    const std::vector<ref<point_light>>& get_point_lights() const { return m_point_lights; }
    std::vector<ref<point_light>>& get_point_lights() { return m_point_lights; }

    void add_spot_light(ref<spot_light> t_light) {
        m_spot_lights.push_back(t_light);
    }
    const std::vector<ref<spot_light>>& get_spot_lights() const { return m_spot_lights; }
    std::vector<ref<spot_light>>& get_spot_lights() { return m_spot_lights; }

private:

    std::vector<ref<light>> m_lights;
    std::vector<ref<directional_light>> m_directional_lights;
    std::vector<ref<point_light>> m_point_lights;
    std::vector<ref<spot_light>> m_spot_lights;

    ref<shader_api> m_shader;

};

}

#endif

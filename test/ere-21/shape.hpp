#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include <glm/glm.hpp>
#include <vector>

#include <ere/api/vertex_array_api.hpp>
#include <ere/api/shader_api.hpp>
#include <ere/api/render_api.hpp>
#include <glm/glm.hpp>
#include "material.hpp"

namespace ere {

class shape {
public:

    virtual void draw(ref<shader_api> t_shader) = 0;
    virtual void draw_textured(ref<shader_api> t_shader, std::vector<ref<texture_api>> t_textures) = 0;

    void set_material(material t_material) { m_material = t_material; }
    material get_material() const { return m_material; }
    material &get_material() { return m_material; }

    glm::vec3 get_pos() const { return m_pos; }
    glm::vec3 &get_pos() { return m_pos; }
    void set_pos(glm::vec3 t_pos) { m_pos = t_pos; }

    float get_rotation() const { return m_rotation; }
    float &get_rotation() { return m_rotation; }
    void set_rotation(float t_rotation) { m_rotation = t_rotation; }

    glm::vec3 get_rotation_axis() const { return m_rotationAxis; }
    glm::vec3 &get_rotation_axis() { return m_rotationAxis; }
    void set_rotation_axis(glm::vec3 t_rotationAxis) { m_rotationAxis = t_rotationAxis; }

    material m_material;
    glm::vec3 m_pos;
    float m_rotation;
    glm::vec3 m_rotationAxis;
};

}

#endif // __SHAPE_HPP__

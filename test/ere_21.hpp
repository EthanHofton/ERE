#ifndef __ERE_21_HPP__
#define __ERE_21_HPP__

#include <ere/core/layer.hpp>
#include <ere/core/camera_3d.hpp>
#include <ere/core/application.hpp>
#include <ere/api/render_api.hpp>
#include <ere/mappings/mouse_map.hpp>
#include <ere/events/window_events.hpp>
#include <imgui.h>

namespace ere {

struct material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

struct light {
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class shape {
public:
    virtual void draw(ref<shader_api> t_shader) = 0;
    void set_material(material t_material) { m_material = t_material; }
    material get_material() const { return m_material; }
    material &get_material() { return m_material; }
    glm::vec3 get_pos() const { return m_pos; }
    glm::vec3 &get_pos() { return m_pos; }
    void set_pos(glm::vec3 t_pos) { m_pos = t_pos; }

    material m_material;
    glm::vec3 m_pos;
};

class sphere : public shape {
public:

    sphere(float t_radius, glm::vec3 t_pos, float t_rotSpeed) {
        m_radius = t_radius;
        m_rotSpeed = t_rotSpeed;
        m_pos = t_pos;

        int numSlices = 50;
        int numStacks = 50;
        float phiStep = glm::two_pi<float>() / numSlices;
        float thetaStep = glm::pi<float>() / numStacks;

        // Generate vertices
        for (int i = 0; i <= numStacks; i++) {
            float theta = i * thetaStep;
            float sinTheta = glm::sin(theta);
            float cosTheta = glm::cos(theta);

            for (int j = 0; j <= numSlices; j++) {
                float phi = j * phiStep;
                float sinPhi = glm::sin(phi);
                float cosPhi = glm::cos(phi);

                glm::vec3 vertex = glm::vec3(cosPhi * sinTheta, cosTheta, sinPhi * sinTheta) * m_radius;
                m_vertices.push_back(vertex);
                m_normals.push_back(glm::normalize(vertex));

                int vertexIndex = i * (numSlices + 1) + j;

                m_indices.push_back(vertexIndex);
                m_indices.push_back(vertexIndex + numSlices + 1);
                m_indices.push_back(vertexIndex + 1);

                m_indices.push_back(vertexIndex + 1);
                m_indices.push_back(vertexIndex + numSlices + 1);
                m_indices.push_back(vertexIndex + numSlices + 2);
            }
        }

        // create the vertex array object
        m_vao = vertex_array_api::create_vertex_array_api();

        // create the vertex buffer object
        m_vbo_pos = vertex_buffer_api::create_vertex_buffer_api(m_vertices.data(), m_vertices.size() * sizeof(glm::vec3));
        m_vbo_pos->set_layout({
            { "aPos", buffer_layout::shader_type::float_3, false }
        });

        // create the vertex buffer object
        m_vbo_norm = vertex_buffer_api::create_vertex_buffer_api(m_normals.data(), m_normals.size() * sizeof(glm::vec3));
        m_vbo_norm->set_layout({
            { "aNorm", buffer_layout::shader_type::float_3, false }
        });

        // add the vertex buffer objects to the vertex array object
        m_vao->add_vertex_buffer(m_vbo_pos);
        m_vao->add_vertex_buffer(m_vbo_norm);

        // create the index buffer object
        ref<index_buffer_api> ibo = index_buffer_api::create_index_buffer_api(m_indices.data(), m_indices.size() * sizeof(uint32_t));

        // add the index buffer object to the vertex array object
        m_vao->set_index_buffer(ibo);

        m_model = glm::translate(m_model, t_pos);
    }

    void draw(ref<shader_api> t_shader) override {
        m_model = glm::mat4(1.0f);
        m_model = glm::translate(m_model, m_pos);
        m_model = glm::rotate(m_model, glm::radians(m_rotSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
        m_rotSpeed += 0.1f;
        if (m_rotSpeed > 360.0f) {
            m_rotSpeed = 0.0f;
        }

        // set model matrix
        t_shader->set_uniform_mat4f("u_model", m_model);

        // set material properties
        t_shader->set_uniform_3f("material.ambient", get_material().ambient);
        t_shader->set_uniform_3f("material.diffuse", get_material().diffuse);
        t_shader->set_uniform_3f("material.specular", get_material().specular);
        t_shader->set_uniform_1f("material.shininess", get_material().shininess);

        // draw the object
        render_api::draw_indexed(m_vao, t_shader);
    }

public:

    float m_radius;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<uint32_t> m_indices;

    ref<vertex_array_api> m_vao;
    ref<vertex_buffer_api> m_vbo_pos;
    ref<vertex_buffer_api> m_vbo_norm;

    float m_rotSpeed;

    glm::mat4 m_model = glm::mat4(1.0f);

};

class cube : public shape {
public:

    cube(glm::vec3 t_size, glm::vec3 t_pos, float t_rotSpeed) {
        m_size = t_size;
        m_rotSpeed = t_rotSpeed;
        m_pos = t_pos;

        m_vertices = {
            // front
            { -m_size.x / 2.0f, -m_size.y / 2.0f,  m_size.z / 2.0f },
            {  m_size.x / 2.0f, -m_size.y / 2.0f,  m_size.z / 2.0f },
            {  m_size.x / 2.0f,  m_size.y / 2.0f,  m_size.z / 2.0f },
            { -m_size.x / 2.0f,  m_size.y / 2.0f,  m_size.z / 2.0f },
            // back
            { -m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f },
            {  m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f },
            {  m_size.x / 2.0f,  m_size.y / 2.0f, -m_size.z / 2.0f },
            { -m_size.x / 2.0f,  m_size.y / 2.0f, -m_size.z / 2.0f }
        };

        m_normals = {
            // front
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            // back
            { 0.0f, 0.0f, -1.0f },
            { 0.0f, 0.0f, -1.0f },
            { 0.0f, 0.0f, -1.0f },
            { 0.0f, 0.0f, -1.0f }
        };

        m_indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // back
            4, 5, 6,
            6, 7, 4,
            // left
            4, 0, 3,
            3, 7, 4,
            // right
            1, 5, 6,
            6, 2, 1,
            // top
            3, 2, 6,
            6, 7, 3,
            // bottom
            4, 5, 1,
            1, 0, 4
        };

        // create the vertex array object
        m_vao = vertex_array_api::create_vertex_array_api();

        // create the vertex buffer object
        m_vbo_pos = vertex_buffer_api::create_vertex_buffer_api(m_vertices.data(), m_vertices.size() * sizeof(glm::vec3));
        m_vbo_pos->set_layout({
            { "aPos", buffer_layout::shader_type::float_3, false }
        });

        // create the vertex buffer object
        m_vbo_norm = vertex_buffer_api::create_vertex_buffer_api(m_normals.data(), m_normals.size() * sizeof(glm::vec3));
        m_vbo_norm->set_layout({
            { "aNorm", buffer_layout::shader_type::float_3, false }
        });

        // add the vertex buffer objects to the vertex array object
        m_vao->add_vertex_buffer(m_vbo_pos);
        m_vao->add_vertex_buffer(m_vbo_norm);

        // create the index buffer object
        ref<index_buffer_api> ibo = index_buffer_api::create_index_buffer_api(m_indices.data(), m_indices.size() * sizeof(uint32_t));

        // add the index buffer object to the vertex array object
        m_vao->set_index_buffer(ibo);

        m_model = glm::translate(m_model, t_pos);
    }

    void draw(ref<shader_api> t_shader) override {
        m_model = glm::mat4(1.0f);
        m_model = glm::translate(m_model, m_pos);
        m_model = glm::rotate(m_model, glm::radians(m_rotSpeed), glm::vec3(0.0f, 1.0f, 0.0f));

        m_rotSpeed += 0.1f;
        if (m_rotSpeed > 360.0f) {
            m_rotSpeed = 0.0f;
        }

        // set model matrix
        t_shader->set_uniform_mat4f("u_model", m_model);

        // set material properties
        t_shader->set_uniform_3f("material.ambient", get_material().ambient);
        t_shader->set_uniform_3f("material.diffuse", get_material().diffuse);
        t_shader->set_uniform_3f("material.specular", get_material().specular);
        t_shader->set_uniform_1f("material.shininess", get_material().shininess);

        // draw the cube
        render_api::draw_indexed(m_vao, t_shader);
    }


public:

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<uint32_t> m_indices;

    ref<vertex_array_api> m_vao;
    ref<vertex_buffer_api> m_vbo_pos;
    ref<vertex_buffer_api> m_vbo_norm;

    glm::mat4 m_model = glm::mat4(1.0f);
    float m_rotSpeed = 0.5f;

    glm::vec3 m_size;

};


class ere_21 : public layer {
public:

    bool on_attach(attach_event& e) override {
        m_camera = createRef<camera_3d>(application::get_application()->get_window_size().x / application::get_application()->get_window_size().y);
        render_api::set_camera(m_camera);

        m_lightCubeShader = shader_api::create_shader_api_from_file("assets/shaders/ere-21/vertex.glsl", "assets/shaders/ere-21/fragment.glsl");
        m_lightSource = createRef<cube>(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-2.0f, 0.0f, 0.0f), 0.1f);
        m_lightSource->set_material({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) });

        m_lightShader = shader_api::create_shader_api_from_file("assets/shaders/ere-21/light_vertex.glsl", "assets/shaders/ere-21/light_fragment.glsl");
        m_shapes.push_back(createRef<sphere>(1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0.1f));
        m_shapes.push_back(createRef<sphere>(0.5f, glm::vec3(2.0f, 0.0f, 0.0f), -0.2f));

        m_shapes[0]->set_material({ glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f * 128.0f });
        m_shapes[1]->set_material({ glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f * 128.0f });

        m_shapes.push_back(m_lightSource);

        return true;
    }

    bool on_update(update_event& e) override {
        m_camera->on_update(e);

        m_lightShader->set_uniform_3f("light.position", m_lightSource->get_pos());
        m_lightShader->set_uniform_3f("light.ambient", m_lightSource->get_material().ambient);
        m_lightShader->set_uniform_3f("light.diffuse", m_lightSource->get_material().diffuse);
        m_lightShader->set_uniform_3f("light.specular", m_lightSource->get_material().specular);

        for (int i = 0; i < m_shapes.size(); i++) {
            m_shapes[i]->draw(m_lightShader);
        }

        // m_lightSource->draw(m_lightCubeShader);

        return true;
    }

    bool on_imgui_update(imgui_update_event& e) override {
        for (int i = 0; i < m_shapes.size(); i++) {
            ImGui::Begin(("Lighting Sphere " + std::to_string(i + 1)).c_str());
            ImGui::ColorEdit3("Ambient", &m_shapes[i]->get_material().ambient[0]);
            ImGui::ColorEdit3("Diffuse", &m_shapes[i]->get_material().diffuse[0]);
            ImGui::ColorEdit3("Specular", &m_shapes[i]->get_material().specular[0]);
            ImGui::SliderFloat("Shininess", &m_shapes[i]->get_material().shininess, 0.0f, 256.0f);
            ImGui::SliderFloat3("Position", &m_shapes[i]->get_pos()[0], -10.0f, 10.0f);
            ImGui::End();
        }

        ImGui::Begin("Light Source");
        ImGui::ColorEdit3("Ambient", &m_lightSource->get_material().ambient[0]);
        ImGui::ColorEdit3("Diffuse", &m_lightSource->get_material().diffuse[0]);
        ImGui::ColorEdit3("Specular", &m_lightSource->get_material().specular[0]);
        ImGui::SliderFloat3("Position", &m_lightSource->get_pos()[0], -10.0f, 10.0f);
        ImGui::End();

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

private:

    ref<camera_3d> m_camera;

    std::vector<ref<shape>> m_shapes;
    ref<cube> m_lightSource;

    ref<shader_api> m_lightShader;
    ref<shader_api> m_lightCubeShader;

    bool m_wireframe = false;



};

}

#endif

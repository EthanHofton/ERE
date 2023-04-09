#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "shape.hpp"

#include <vector>

#include <ere/api/vertex_array_api.hpp>
#include <ere/api/shader_api.hpp>
#include <ere/api/render_api.hpp>
#include <glm/glm.hpp>

namespace ere {

class sphere : public shape {
public:

    sphere(float t_radius, glm::vec3 t_pos) {
        m_radius = t_radius;
        m_pos = t_pos;
        m_rotation = 0.f;
        m_rotationAxis = { 0.f, 0.f, 0.f };

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

        m_model = glm::mat4(1.0f);
        m_model = glm::translate(m_model, t_pos);
        // m_model = glm::rotate(m_model, glm::radians(m_rotation), m_rotationAxis);
    }

    void draw(ref<shader_api> t_shader) override {
        m_model = glm::mat4(1.0f);
        m_model = glm::translate(m_model, m_pos);
        // m_model = glm::rotate(m_model, glm::radians(m_rotation), m_rotationAxis);

        // set model matrix
        t_shader->set_uniform_mat4f("u_model", m_model);

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

    glm::mat4 m_model = glm::mat4(1.0f);
};

}

#endif

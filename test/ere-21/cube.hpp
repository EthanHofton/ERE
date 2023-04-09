#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include "shape.hpp"

#include <vector>

#include <ere/api/vertex_array_api.hpp>
#include <ere/api/shader_api.hpp>
#include <ere/api/render_api.hpp>
#include <glm/glm.hpp>

namespace ere {

class cube : public shape {
public:

    cube(glm::vec3 t_size, glm::vec3 t_pos) {
        m_size = t_size;
        m_pos = t_pos;
        m_rotation = 0.f;
        m_rotationAxis = { 0.f, 0.f, 0.f };

        // front, back, left, right, top, bottom faces vertices
        m_vertices = {
            // front face
            { -m_size.x / 2.f, -m_size.y / 2.f,  m_size.z / 2.f },
            {  m_size.x / 2.f, -m_size.y / 2.f,  m_size.z / 2.f },
            {  m_size.x / 2.f,  m_size.y / 2.f,  m_size.z / 2.f },
            { -m_size.x / 2.f,  m_size.y / 2.f,  m_size.z / 2.f },
            // back face
            { -m_size.x / 2.f, -m_size.y / 2.f, -m_size.z / 2.f },
            {  m_size.x / 2.f, -m_size.y / 2.f, -m_size.z / 2.f },
            {  m_size.x / 2.f,  m_size.y / 2.f, -m_size.z / 2.f },
            { -m_size.x / 2.f,  m_size.y / 2.f, -m_size.z / 2.f },
            // left face
            { -m_size.x / 2.f, -m_size.y / 2.f, -m_size.z / 2.f },
            { -m_size.x / 2.f, -m_size.y / 2.f,  m_size.z / 2.f },
            { -m_size.x / 2.f,  m_size.y / 2.f,  m_size.z / 2.f },
            { -m_size.x / 2.f,  m_size.y / 2.f, -m_size.z / 2.f },
            // right face
            {  m_size.x / 2.f, -m_size.y / 2.f, -m_size.z / 2.f },
            {  m_size.x / 2.f, -m_size.y / 2.f,  m_size.z / 2.f },
            {  m_size.x / 2.f,  m_size.y / 2.f,  m_size.z / 2.f },
            {  m_size.x / 2.f,  m_size.y / 2.f, -m_size.z / 2.f },
            // top face
            { -m_size.x / 2.f,  m_size.y / 2.f, -m_size.z / 2.f },
            {  m_size.x / 2.f,  m_size.y / 2.f, -m_size.z / 2.f },
            {  m_size.x / 2.f,  m_size.y / 2.f,  m_size.z / 2.f },
            { -m_size.x / 2.f,  m_size.y / 2.f,  m_size.z / 2.f },
            // bottom face
            { -m_size.x / 2.f, -m_size.y / 2.f, -m_size.z / 2.f },
            {  m_size.x / 2.f, -m_size.y / 2.f, -m_size.z / 2.f },
            {  m_size.x / 2.f, -m_size.y / 2.f,  m_size.z / 2.f },
            { -m_size.x / 2.f, -m_size.y / 2.f,  m_size.z / 2.f }
        };

        m_normals = {
            // front face
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },
            // back face
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },
            // left face
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },
            // right face
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },
            // top face
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },
            // bottom face
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f }
        };

        m_indices = {
            // front face
            0, 1, 2,
            2, 3, 0,
            // back face
            4, 5, 6,
            6, 7, 4,
            // left face
            8, 9, 10,
            10, 11, 8,
            // right face
            12, 13, 14,
            14, 15, 12,
            // top face
            16, 17, 18,
            18, 19, 16,
            // bottom face
            20, 21, 22,
            22, 23, 20
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

        // draw the cube
        render_api::draw_indexed(m_vao, t_shader);
    }


public:

    glm::vec3 m_size;

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<uint32_t> m_indices;

    ref<vertex_array_api> m_vao;
    ref<vertex_buffer_api> m_vbo_pos;
    ref<vertex_buffer_api> m_vbo_norm;

    glm::mat4 m_model = glm::mat4(1.0f);
};

}

#endif // __CUBE_HPP__

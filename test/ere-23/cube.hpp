#ifndef __ERE_23_CUBE_HPP__
#define __ERE_23_CUBE_HPP__

#include <vector>

#include <ere/api/vertex_array_api.hpp>
#include <ere/api/shader_api.hpp>
#include <ere/api/render_api.hpp>
#include <glm/glm.hpp>

namespace ere {

class cube {
public:

    cube(glm::vec3 t_size) {
        m_size = t_size;

        m_vertices = {
            // front
            { -m_size.x, -m_size.y,  m_size.z },
            {  m_size.x, -m_size.y,  m_size.z },
            {  m_size.x,  m_size.y,  m_size.z },
            { -m_size.x,  m_size.y,  m_size.z },
            // back
            { -m_size.x, -m_size.y, -m_size.z },
            {  m_size.x, -m_size.y, -m_size.z },
            {  m_size.x,  m_size.y, -m_size.z },
            { -m_size.x,  m_size.y, -m_size.z },
        };

        // indices in face culling winding order (CCW)
        m_indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
        };

        // create the vertex array object
        m_vao = vertex_array_api::create_vertex_array_api();

        // create the vertex buffer object
        m_vbo_pos = vertex_buffer_api::create_vertex_buffer_api(m_vertices.data(), m_vertices.size() * sizeof(glm::vec3));
        m_vbo_pos->set_layout({
            { "aPos", buffer_layout::shader_type::float_3 }
        });

        // add the vertex buffer objects to the vertex array object
        m_vao->add_vertex_buffer(m_vbo_pos);

        // create the index buffer object
        ref<index_buffer_api> ibo = index_buffer_api::create_index_buffer_api(m_indices.data(), m_indices.size() * sizeof(uint32_t));

        // add the index buffer object to the vertex array object
        m_vao->set_index_buffer(ibo);
    }

public:

    glm::vec3 m_size;

    std::vector<glm::vec3> m_vertices;
    std::vector<uint32_t> m_indices;

    ref<vertex_array_api> m_vao;
    ref<vertex_buffer_api> m_vbo_pos;
};

}

#endif

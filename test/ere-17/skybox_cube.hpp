#ifndef __SKYBOX_CUBE_HPP__
#define __SKYBOX_CUBE_HPP__

#include <ere/api/vertex_array_api.hpp>
#include <ere/api/vertex_buffer_api.hpp>
#include <ere/api/index_buffer_api.hpp>
#include <glm/glm.hpp>

namespace ere {

class skybox_cube {
public:

    skybox_cube() {
        m_vertices = {
            // positions          
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),

            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),

            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3( 1.0f,  1.0f, -1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3( 1.0f, -1.0f,  1.0f)
        };

        m_vao = vertex_array_api::create_vertex_array_api();

        m_vbo = vertex_buffer_api::create_vertex_buffer_api(m_vertices.data(), m_vertices.size() * sizeof(glm::vec3));
        m_vbo->set_layout({
            { "a_Pos", buffer_layout::shader_type::float_3, false }
        });

        m_vao->add_vertex_buffer(m_vbo);
    }

public:

    ref<vertex_array_api> m_vao;
    ref<vertex_buffer_api> m_vbo;

    std::vector<glm::vec3> m_vertices;

};

}

#endif // __SKYBOX_CUBE_HPP__

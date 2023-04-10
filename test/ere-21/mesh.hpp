#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <ere/api/render_api.hpp>
#include <ere/api/texture_api.hpp>
#include <ere/core/camera_3d.hpp>
#include "material.hpp"

namespace ere {

struct mesh {
public:

    mesh(const std::vector<glm::vec3>& t_vertices, const std::vector<glm::vec2>& t_uv, const std::vector<glm::vec3>& t_normals, const std::vector<unsigned int>& t_indices) {

        // create the vao
        m_vao = vertex_array_api::create_vertex_array_api();

        m_vertices = t_vertices;
        m_uv = t_uv;
        m_normals = t_normals;
        m_indices = t_indices;

        // create the vbos
        m_vbo_vetices = vertex_buffer_api::create_vertex_buffer_api(m_vertices.data(), m_vertices.size() * sizeof(glm::vec3));
        m_vbo_normals = vertex_buffer_api::create_vertex_buffer_api(m_uv.data(), m_uv.size() * sizeof(glm::vec3));
        m_vbo_uv = vertex_buffer_api::create_vertex_buffer_api(m_uv.data(), m_uv.size() * sizeof(glm::vec2));

        // create the ibo
        m_ibo = index_buffer_api::create_index_buffer_api(m_indices.data(), m_indices.size() * sizeof(uint32_t));

        buffer_layout layout_vertices = {
            { "aPosition", buffer_layout::shader_type::float_3, false },
        };

        buffer_layout layout_normals = {
            { "aNormal", buffer_layout::shader_type::float_3, false },
        };

        buffer_layout layout_uv = {
            { "aUv", buffer_layout::shader_type::float_2, false },
        };


        m_vbo_vetices->set_layout(layout_vertices);
        m_vbo_normals->set_layout(layout_normals);
        m_vbo_uv->set_layout(layout_uv);

        // add the vbos to the vao
        m_vao->add_vertex_buffer(m_vbo_vetices);
        m_vao->add_vertex_buffer(m_vbo_normals);
        m_vao->add_vertex_buffer(m_vbo_uv);

        // add the ibo to the vao
        m_vao->set_index_buffer(m_ibo);
    }

    void draw(ref<shader_api> t_shader) {
        glm::mat4 model = glm::mat4(1.0f);
        t_shader->set_uniform_mat4f("u_model", model);
        render_api::draw_indexed_textured(m_vao, t_shader, { m_material.diffuse_texture, m_material.specular_texture, m_material.emission_texture });
    }

    void set_material(const material& t_material) { m_material = t_material; }
    material& get_material() { return m_material; }

private:

    ref<vertex_array_api> m_vao;

    ref<vertex_buffer_api> m_vbo_vetices;
    ref<vertex_buffer_api> m_vbo_uv;
    ref<vertex_buffer_api> m_vbo_normals;

    ref<index_buffer_api> m_ibo;
    
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_uv;
    std::vector<glm::vec3> m_normals;
    std::vector<uint32_t> m_indices;

    material m_material;
};


}

#endif

#ifndef ERE_COMPONENT_MESH_HPP
#define ERE_COMPONENT_MESH_HPP

#include <vector>
#include <glm/glm.hpp>

namespace ere {


struct mesh {

    struct vertex {
        glm::vec3 m_pos;
        glm::vec3 m_normal;
        glm::vec3 m_tangent;
        glm::vec2 m_uv1;
        glm::vec2 m_uv2;
        glm::vec2 m_uv3;
        glm::vec2 m_uv4;
        glm::vec4 m_color;
    };

    using iterator = std::vector<vertex>::iterator;
    using const_iterator = std::vector<vertex>::const_iterator;

    iterator begin() { return m_vertices.begin(); }
    const_iterator begin() const { return m_vertices.begin(); }
    const_iterator cbegin() const { return m_vertices.cbegin(); }

    iterator end() { return m_vertices.end(); }
    const_iterator end() const { return m_vertices.end(); }
    const_iterator cend() const { return m_vertices.cend(); }

private:

    std::vector<vertex> m_vertices;
    std::vector<unsigned int> m_submeshOffsets = {0};
};

}

#endif

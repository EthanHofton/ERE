#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include <glm/glm.hpp>
#include <ere/api/texture2d_api.hpp>

namespace ere {

struct material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    ref<texture2d_api> diffuse_texture = nullptr;
    ref<texture2d_api> specular_texture = nullptr;
    ref<texture2d_api> emission_texture = nullptr;
};

}

#endif // __MATERIAL_HPP__

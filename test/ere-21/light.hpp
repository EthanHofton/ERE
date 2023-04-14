#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <glm/glm.hpp>

namespace ere {

struct light {
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct directional_light {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct point_light {
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct spot_light {
    glm::vec3 position;
    glm::vec3 direction;

    float cut_off;
    float outer_cut_off;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

} // namespace ere

#endif // __LIGHT_HPP__

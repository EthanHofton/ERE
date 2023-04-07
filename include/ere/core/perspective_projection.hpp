#ifndef __ERE_PERSPECTIVE_PROJECTION_HPP__
#define __ERE_PERSPECTIVE_PROJECTION_HPP__

#include <ere/api/projection_api.hpp>

namespace ere {

class perspective_projection : public projection_api {
public:

    perspective_projection(float t_fov, float t_aspect, float t_near, float t_far)
        : m_fov(t_fov), m_aspect(t_aspect), m_near(t_near), m_far(t_far) {
        m_projection_matrix = glm::perspective(m_fov, m_aspect, m_near, m_far);
    }

    glm::mat4 get_projection_matrix() const override {
        return m_projection_matrix;
    }

private:

    float m_fov, m_aspect, m_near, m_far;
    glm::mat4 m_projection_matrix;

};

}


#endif // __ERE_PERSPECTIVE_PROJECTION_HPP__

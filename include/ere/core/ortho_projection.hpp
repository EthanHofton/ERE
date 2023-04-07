#ifndef __ERE_ORTHO_PROJECTION_HPP__
#define __ERE_ORTHO_PROJECTION_HPP__

#include <ere/api/projection_api.hpp>

namespace ere {

class ortho_projection : public projection_api {
public:

    ortho_projection(float t_left, float t_right, float t_bottom, float t_top, float t_near, float t_far)
        : m_left(t_left), m_right(t_right), m_bottom(t_bottom), m_top(t_top), m_near(t_near), m_far(t_far) {
        m_projection_matrix = glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
    }

    glm::mat4 get_projection_matrix() const override {
        return m_projection_matrix;
    }

private:

    float m_left, m_right, m_bottom, m_top, m_near, m_far;
    glm::mat4 m_projection_matrix;

};

}


#endif // __ERE_ORTHO_PROJECTION_HPP__

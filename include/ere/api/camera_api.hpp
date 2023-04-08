#ifndef __ERE_CAMERA_API_HPP__
#define __ERE_CAMERA_API_HPP__

#include <glm/gtc/matrix_transform.hpp>
#include <ere/events/events.hpp>

namespace ere {

class camera_api {
public:

    ~camera_api() = default;

    virtual const glm::mat4& get_view_matrix() = 0;
    virtual const glm::mat4& get_projection_matrix() = 0;

};

} // namespace ere

#endif // __ERE_CAMERA_API_HPP__

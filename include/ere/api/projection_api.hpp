#ifndef __ERE_PROJECTION_API_HPP__
#define __ERE_PROJECTION_API_HPP__

#include <glm/gtc/matrix_transform.hpp>

namespace ere {

class projection_api {
public:

    virtual ~projection_api() = default;
    virtual glm::mat4 get_projection_matrix() const = 0;
};

}


#endif // __ERE_PROJECTION_API_HPP__

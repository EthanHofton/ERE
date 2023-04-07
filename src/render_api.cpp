#include <ere/api/render_api.hpp>

namespace ere {

glm::mat4 render_api::s_projection_matrix = glm::mat4(1.0f);
glm::mat4 render_api::s_view_matrix = glm::mat4(1.0f);
util::raii_timer render_api::s_timer = util::raii_timer();

}

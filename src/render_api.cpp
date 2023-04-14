#include <ere/api/render_api.hpp>

namespace ere {

ref<camera_api> render_api::s_camera = nullptr;
util::raii_timer render_api::s_timer = util::raii_timer();

}

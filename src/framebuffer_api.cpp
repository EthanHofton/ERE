#include <ere/api/framebuffer_api.hpp>

namespace ere {

ref<framebuffer_api> framebuffer_api::s_default_framebuffer;
weak_ref<framebuffer_api> framebuffer_api::s_current_framebuffer;

}

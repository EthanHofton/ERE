#include <ere/core/application.hpp>

namespace ere {

ref<application> application::create_application() {
    return createRef<application>();
}

application::application() {
    ERE_INFO("Application created");
}

application::~application() {
    ERE_INFO("Application destroyed");
}

}

#include <ere/core/entry_point.hpp>
#include <iostream>

namespace ere {

ref<ere::application> ere_create_application() {
    ref<application> app = application::create_application();

    return app;
}

}

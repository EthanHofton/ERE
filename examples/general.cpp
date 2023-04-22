#include <ere/core/entry_point.hpp>
// #include "ere-21/model_lighting.hpp"
// #include "ere-21/ere_21.hpp"
// #include "ere-17/ere_17.hpp"
#include "ere-23/ere_23.hpp"


namespace ere {

ref<ere::application> ere_create_application() {
    ref<application> app = application::get_application();

    app->push_layer(createRef<ere_23>());

    // app->set_background_color({.529f, .808f, .922f, 1.0f});
    app->set_background_color({0.f, 0.f, 0.f, 1.0f});
    app->set_fps(120.0);
    app->set_window_title("Ere Engine TEST CHANGE");
    app->vsync(false);
    app->set_relative_mouse_mode(true);

    return app;
}

}
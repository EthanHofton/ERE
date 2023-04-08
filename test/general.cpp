#include "model_loading.hpp"
#include "layer_test.hpp"


namespace ere {

ref<ere::application> ere_create_application() {
    ref<application> app = application::get_application();

    app->push_layer(createRef<model_layer>());

    app->set_background_color({.529f, .808f, .922f, 1.0f});
    app->set_fps(120.0);
    app->set_window_title("Ere Engine TEST CHANGE");
    app->vsync(false);
    app->set_relative_mouse_mode(true);

    return app;
}

}

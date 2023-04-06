#include <ere/core/entry_point.hpp>
#include <ere/core/layer.hpp>
#include <ere/mappings/key_map.hpp>
#include <imgui.h>
#include <ere/api/render_api.hpp>

#include <iostream>

namespace ere {

class l1 : public layer {
public:

    bool on_key_pressed(key_pressed_event& e) override {
        if (e.get_key_code() == ERE_KEY_C) {
            application::get_application()->set_background_color({0.1f, 1.f, 0.1f, 1.0f});
        }
        return true;
    }


    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowDemoWindow();
        return false;
    }
};

ref<ere::application> ere_create_application() {
    ref<application> app = application::get_application();

    app->push_layer(createRef<l1>());

    app->set_background_color({0.1f, 0.1f, 0.1f, 1.0f});
    app->set_fps(120.0);
    app->set_window_title("Ere Engine TEST CHANGE");
    app->vsync(false);
    
    // *** TEST ***
    shader_api::create_shader_api_from_file("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

    return app;
}

}

#include <ere/core/entry_point.hpp>
#include <ere/core/layer.hpp>
#include <imgui.h>

#include <iostream>

namespace ere {

class l1 : public layer {
public:

    bool on_key_pressed(key_pressed_event& e) override {
        ERE_INFO("Key Event: {}", e.toString());
        return true;
    }


    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowDemoWindow();
        return false;
    }
};

ref<ere::application> ere_create_application() {
    ref<application> app = application::create_application();

    app->push_layer(createRef<l1>());

    return app;
}

}

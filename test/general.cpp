#include <ere/core/entry_point.hpp>
#include <ere/core/layer.hpp>

#include <iostream>

namespace ere {

class l1 : public layer {
public:

    bool on_key_pressed(key_pressed_event& e) override {
        ERE_INFO("Key Event: {}", e.toString());
        return true;
    }


};

ref<ere::application> ere_create_application() {
    ref<application> app = application::create_application();

    app->push_layer(createRef<l1>());

    return app;
}

}

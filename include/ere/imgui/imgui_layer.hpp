#ifndef ERE_IMGUI_LAYER_HPP
#define ERE_IMGUI_LAYER_HPP

#include <ere/core/layer.hpp>

namespace ere {

class imgui_layer : public layer {
public:

    void begin(const double& t_delta, const glm::vec2& t_window_size, const glm::vec2& t_framebuff_size);
    void end();

    virtual bool on_attach(attach_event& t_e) final override;
    virtual bool on_detach(detach_event& t_e) final override;

    virtual bool on_key_pressed(key_pressed_event& t_e) final override;
    virtual bool on_key_released(key_released_event& t_e) final override;
    virtual bool on_key_typed(key_typed_event& t_e) final override;
    virtual bool on_mouse_button_pressed(mouse_button_pressed_event& t_e) final override;
    virtual bool on_mouse_button_released(mouse_button_released_event& t_e) final override;
    virtual bool on_mouse_moved(mouse_moved_event& t_e) final override;
    virtual bool on_mouse_scrolled(mouse_scrolled_event& t_e) final override;
    virtual bool on_window_resized(window_resized_event& t_e) final override;
    virtual bool on_window_framebuffer_resized(window_framebuffer_resized_event& t_e) final override;

};

}

#endif

#include <ere/core/layer.hpp>

namespace ere {

void layer::on_event(ere_event& t_event) {
    util::event_dispatcher<ere_events> dispatcher(t_event);

    /* -- application events -- */
    dispatcher.dispatch<update_event>(std::bind(&layer::on_update, this, std::placeholders::_1));
    dispatcher.dispatch<attach_event>(std::bind(&layer::on_attach, this, std::placeholders::_1));
    dispatcher.dispatch<detach_event>(std::bind(&layer::on_detach, this, std::placeholders::_1));
    dispatcher.dispatch<imgui_update_event>(std::bind(&layer::on_imgui_update, this, std::placeholders::_1));

    /* -- window events -- */
    dispatcher.dispatch<window_closed_event>(std::bind(&layer::on_window_closed, this, std::placeholders::_1));
    dispatcher.dispatch<window_moved_event>(std::bind(&layer::on_window_moved, this, std::placeholders::_1));
    dispatcher.dispatch<window_resized_event>(std::bind(&layer::on_window_resized, this, std::placeholders::_1));
    dispatcher.dispatch<window_framebuffer_resized_event>(std::bind(&layer::on_window_framebuffer_resized, this, std::placeholders::_1));
    dispatcher.dispatch<window_focus_event>(std::bind(&layer::on_window_focus, this, std::placeholders::_1));
    dispatcher.dispatch<window_lost_focus_event>(std::bind(&layer::on_window_lost_focus, this, std::placeholders::_1));
    dispatcher.dispatch<window_maximized_event>(std::bind(&layer::on_window_maximized, this, std::placeholders::_1));
    dispatcher.dispatch<window_minimized_event>(std::bind(&layer::on_window_minimized, this, std::placeholders::_1));
    dispatcher.dispatch<window_restored_event>(std::bind(&layer::on_window_restored, this, std::placeholders::_1));

    /* -- key events -- */
    dispatcher.dispatch<key_pressed_event>(std::bind(&layer::on_key_pressed, this, std::placeholders::_1));
    dispatcher.dispatch<key_released_event>(std::bind(&layer::on_key_released, this, std::placeholders::_1));
    dispatcher.dispatch<key_typed_event>(std::bind(&layer::on_key_typed, this, std::placeholders::_1));

    /* -- mouse events -- */
    dispatcher.dispatch<mouse_button_pressed_event>(std::bind(&layer::on_mouse_button_pressed, this, std::placeholders::_1));
    dispatcher.dispatch<mouse_button_released_event>(std::bind(&layer::on_mouse_button_released, this, std::placeholders::_1));
    dispatcher.dispatch<mouse_moved_event>(std::bind(&layer::on_mouse_moved, this, std::placeholders::_1));
    dispatcher.dispatch<mouse_scrolled_event>(std::bind(&layer::on_mouse_scrolled, this, std::placeholders::_1));
}

}

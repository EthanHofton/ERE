#ifndef __ERE_LAYER_HPP__
#define __ERE_LAYER_HPP__

#include "i_layer.hpp"
#include <ere/events/app_events.hpp>
#include <ere/events/window_events.hpp>
#include <ere/events/mouse_events.hpp>
#include <ere/events/key_events.hpp>

namespace ere {

class layer : public i_layer {
public:

    virtual void on_event(ere_event& t_event) override final;

    /* -- application events -- */
    inline virtual bool on_update(update_event& t_event) { return false; }
    inline virtual bool on_attach(attach_event& t_event) { return false; }
    inline virtual bool on_detach(detach_event& t_event) { return false; }
    inline virtual bool on_imgui_update(imgui_update_event& t_event) { return false; }

    /* -- window events -- */
    inline virtual bool on_window_closed(window_closed_event& t_event) { return false; }
    inline virtual bool on_window_moved(window_moved_event& t_event) { return false; }
    inline virtual bool on_window_resized(window_resized_event& t_event) { return false; }
    inline virtual bool on_window_framebuffer_resized(window_framebuffer_resized_event& t_event) { return false; }
    inline virtual bool on_window_focus(window_focus_event& t_event) { return false; }
    inline virtual bool on_window_lost_focus(window_lost_focus_event& t_event) { return false; }
    inline virtual bool on_window_minimized(window_minimized_event& t_event) { return false; }
    inline virtual bool on_window_maximized(window_maximized_event& t_event) { return false; }
    inline virtual bool on_window_restored(window_restored_event& t_event) { return false; }
    inline virtual bool on_file_dropped(file_dropped_event& t_event) { return false; }

    /* -- key events -- */
    inline virtual bool on_key_pressed(key_pressed_event &t_event) { return false; }
    inline virtual bool on_key_released(key_released_event &t_event) { return false; }
    inline virtual bool on_key_typed(key_typed_event &t_event) { return false; }

    /* -- mouse events -- */
    inline virtual bool on_mouse_button_pressed(mouse_button_pressed_event &t_event) { return false; }
    inline virtual bool on_mouse_button_released(mouse_button_released_event &t_event) { return false; }
    inline virtual bool on_mouse_moved(mouse_moved_event &t_event) { return false; }
    inline virtual bool on_mouse_scrolled(mouse_scrolled_event &t_event) { return false; }
};

}

#endif

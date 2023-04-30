#ifndef __ERE_EVENTS_HPP__
#define __ERE_EVENTS_HPP__

#include <util/event.hpp>

namespace ere {

enum class ere_events {
    /* -- window events -- */
    window_closed, window_moved, window_resized, window_focus, window_lost_focus, window_minimized, window_maximized, window_restored, window_framebuffer_resized, file_dropped,

    /* -- keyboard events -- */
    key_pressed, key_released, key_typed,

    /* -- mouse events -- */
    mouse_button_pressed, mouse_button_released, mouse_moved, mouse_scrolled,

    /* -- application events -- */
    update, attach, detach, imgui_update,
};

using ere_event = util::event<ere_events>;

}

#endif

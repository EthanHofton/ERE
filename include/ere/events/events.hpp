#ifndef ERE_EVENTS_EVENTS_HPP
#define ERE_EVENTS_EVENTS_HPP

#include <util/event.hpp>

namespace ere {

enum class ereEvents {
    /* -- window events -- */
    windowClosed, windowMoved, windowResize, windowFocus, windowLostFocus,
    windowMinimized, windowMaximised, windowRestored,
    /* -- key events -- */
    keyPressed, keyReleased, keyTyped,
    /* -- mouse events -- */
    mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScrolled,
    /* -- app events -- */
    update, attach, detach, imguiUpdate
};

using ereEvent = util::event<ereEvents>;

}

#endif

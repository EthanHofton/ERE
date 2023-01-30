#ifndef ERE_CORE_LAYER_HPP
#define ERE_CORE_LAYER_HPP

#include "iLayer.hpp"
#include <ere/events/appEvents.hpp>
#include <ere/events/windowEvents.hpp>
#include <ere/events/mouseEvents.hpp>
#include <ere/events/keyEvents.hpp>

namespace ere {

class layer : public iLayer {
public:

    virtual void onEvent(ereEvent& t_event) override final;

    /* -- application events -- */
    inline virtual void onUpdate(updateEvent& t_event) {}
    inline virtual void onAttach(attachEvent& t_event) {}
    inline virtual void onDetach(detachEvent& t_event) {}

    /* -- window events -- */
    inline virtual void onWindowClose(windowClosedEvent& t_event) {}
    inline virtual void onWindowMoved(windowMovedEvent& t_event) {}
    inline virtual void onWindowResize(windowResizeEvent& t_event) {}
    inline virtual void onWindowFocus(windowFocusEvent& t_event) {}
    inline virtual void onWindowLostFocus(windowLostFocusEvent& t_event) {}
    inline virtual void onWindowMinimized(windowMinimizedEvent& t_event) {}
    inline virtual void onWindowMaximised(windowMaximisedEvent& t_event) {}
    inline virtual void onWindowRestored(windowRestoredEvent& t_event) {}

    /* -- key events -- */
    inline virtual void onKeyPressed(keyPressedEvent &t_event) {}
    inline virtual void onKeyReleased(keyReleasedEvent &t_event) {}
    inline virtual void onKeyTyped(keyTypedEvent &t_event) {}

    /* -- mouse events -- */
    inline virtual void onMouseButtonPressed(mouseButtonPressedEvent &t_event) {}
    inline virtual void onMouseButtonReleased(mouseButtonReleasedEvent &t_event) {}
    inline virtual void onMouseMoved(mouseMovedEvent &t_event) {}
    inline virtual void onMouseScrolled(mouseScrolledEvent &t_event) {}
};

}

#endif

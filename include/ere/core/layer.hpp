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
    inline virtual bool onUpdate(updateEvent& t_event) {}
    inline virtual bool onAttach(attachEvent& t_event) {}
    inline virtual bool onDetach(detachEvent& t_event) {}
    inline virtual bool onImguiUpdate(imguiUpdateEvent& t_event) {}

    /* -- window events -- */
    inline virtual bool onWindowClose(windowClosedEvent& t_event) {}
    inline virtual bool onWindowMoved(windowMovedEvent& t_event) {}
    inline virtual bool onWindowResize(windowResizeEvent& t_event) {}
    inline virtual bool onWindowFocus(windowFocusEvent& t_event) {}
    inline virtual bool onWindowLostFocus(windowLostFocusEvent& t_event) {}
    inline virtual bool onWindowMinimized(windowMinimizedEvent& t_event) {}
    inline virtual bool onWindowMaximised(windowMaximisedEvent& t_event) {}
    inline virtual bool onWindowRestored(windowRestoredEvent& t_event) {}

    /* -- key events -- */
    inline virtual bool onKeyPressed(keyPressedEvent &t_event) {}
    inline virtual bool onKeyReleased(keyReleasedEvent &t_event) {}
    inline virtual bool onKeyTyped(keyTypedEvent &t_event) {}

    /* -- mouse events -- */
    inline virtual bool onMouseButtonPressed(mouseButtonPressedEvent &t_event) {}
    inline virtual bool onMouseButtonReleased(mouseButtonReleasedEvent &t_event) {}
    inline virtual bool onMouseMoved(mouseMovedEvent &t_event) {}
    inline virtual bool onMouseScrolled(mouseScrolledEvent &t_event) {}
};

}

#endif

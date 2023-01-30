#include <ere/core/layer.hpp>

namespace ere {

void layer::onEvent(ereEvent& t_event) {
    util::event_dispatcher<ere::ereEvents> dispatcher(t_event);

    /* -- application events -- */
    dispatcher.dispatch<updateEvent>(std::bind(&layer::onUpdate, this, std::placeholders::_1));
    dispatcher.dispatch<attachEvent>(std::bind(&layer::onAttach, this, std::placeholders::_1));
    dispatcher.dispatch<detachEvent>(std::bind(&layer::onDetach, this, std::placeholders::_1));
    dispatcher.dispatch<imguiUpdateEvent>(std::bind(&layer::onImguiUpdate, this, std::placeholders::_1));

    /* -- window events -- */
    dispatcher.dispatch<windowClosedEvent>(std::bind(&layer::onWindowClose, this, std::placeholders::_1));
    dispatcher.dispatch<windowMovedEvent>(std::bind(&layer::onWindowMoved, this, std::placeholders::_1));
    dispatcher.dispatch<windowResizeEvent>(std::bind(&layer::onWindowResize, this, std::placeholders::_1));
    dispatcher.dispatch<windowFocusEvent>(std::bind(&layer::onWindowFocus, this, std::placeholders::_1));
    dispatcher.dispatch<windowLostFocusEvent>(std::bind(&layer::onWindowLostFocus, this, std::placeholders::_1));
    dispatcher.dispatch<windowMinimizedEvent>(std::bind(&layer::onWindowMinimized, this, std::placeholders::_1));
    dispatcher.dispatch<windowMaximisedEvent>(std::bind(&layer::onWindowMaximised, this, std::placeholders::_1));
    dispatcher.dispatch<windowRestoredEvent>(std::bind(&layer::onWindowRestored, this, std::placeholders::_1));

    /* -- key events -- */
    dispatcher.dispatch<keyPressedEvent>(std::bind(&layer::onKeyPressed, this, std::placeholders::_1));
    dispatcher.dispatch<keyReleasedEvent>(std::bind(&layer::onKeyReleased, this, std::placeholders::_1));
    dispatcher.dispatch<keyTypedEvent>(std::bind(&layer::onKeyTyped, this, std::placeholders::_1));

    /* -- mouse events -- */
    dispatcher.dispatch<mouseButtonPressedEvent>(std::bind(&layer::onMouseButtonPressed, this, std::placeholders::_1));
    dispatcher.dispatch<mouseButtonReleasedEvent>(std::bind(&layer::onMouseButtonReleased, this, std::placeholders::_1));
    dispatcher.dispatch<mouseMovedEvent>(std::bind(&layer::onMouseMoved, this, std::placeholders::_1));
    dispatcher.dispatch<mouseScrolledEvent>(std::bind(&layer::onMouseScrolled, this, std::placeholders::_1));
}

}

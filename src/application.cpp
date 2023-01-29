#include <ere/core/application.hpp>
#include <iostream>

namespace ere {

application::application(const windowAPI::windowProps& t_props) {
    m_windowAPI = windowAPI::createConcreteWindowAPI();
    m_windowAPI->setEventFunction(std::bind(&application::onEvent, this, std::placeholders::_1));
    m_windowAPI->createWindow(t_props);
}
application::~application() {
    m_windowAPI->destroyWindow();
}

void application::run() {
    while (m_running) {
        m_timer.tick();

        if (m_timer.getDeltaTime() >= 1.0f / m_fps) {
            m_timer.reset();

            m_windowAPI->preRender();

            // * create onUpdate event and propagate
            // * imgui stuff
            
            // * send a window updated event
            updateEvent e(m_timer.getDeltaTime());
            m_windowAPI->sendEvent(e);

            m_windowAPI->postRender();
        }
    }
}

/* -- Events -- */

void application::onEvent(ereEvent& t_event) {
    // * dispatch a window closed event to stop the application loop
    util::event_dispatcher<ereEvents> dispatcher(t_event);
    dispatcher.dispatch<windowClosedEvent>(std::bind(&application::onWindowClose, this, std::placeholders::_1));

    // * propagate events down the event stack
}

bool application::onWindowClose(windowClosedEvent& t_event) {
    m_running = false;
    return false;
}


/* -- WindowAPI -- */

void application::setWindowSize(const glm::vec2& t_size) { m_windowAPI->setWindowSize(t_size); }
void application::setWindowPos(const glm::vec2& t_pos) { m_windowAPI->setWindowPos(t_pos); }
void application::setWindowTitle(const std::string& t_title) { m_windowAPI->setWindowTitle(t_title); }
void application::setWindowSwapInterval(const int& t_swap) { m_windowAPI->setWindowSwapInterval(t_swap); }
void application::setBackgroundColor(const glm::vec4& t_color) { m_windowAPI->setBackgroundColor(t_color); }

glm::vec2 application::getWindowSize() const { return m_windowAPI->getWindowSize(); }
glm::vec2 application::getWindowPos() const { return m_windowAPI->getWindowPos(); }

void application::maximiseWindow() { m_windowAPI->maximizeWindow(); }
void application::minimizeWindow() { m_windowAPI->minimizeWindow(); }
void application::restoreWindow() { m_windowAPI->restoreWindow(); }
void application::focusWindow() { m_windowAPI->focusWindow(); }

}



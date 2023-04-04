#include <ere/core/application.hpp>

namespace ere {

ref<application> application::create_application() {
    return createRef<application>();
}

application::application() {
    ERE_INFO("Application created");
}

application::~application() {
    ERE_INFO("Application destroyed");
}

void application::run() {
    ERE_INFO("Application running");

    // run until the application is closed
    while (m_running) {
        // update the timer
        m_timer.tick();
        // check if the timer has reached the fps
        if (m_timer.getDeltaTime() >= 1.0 / m_fps) {
            // reset the timer if it has
            m_timer.reset();
        }
    }
}

void application::on_event() {
    ERE_TRACE("Application event");
}

}

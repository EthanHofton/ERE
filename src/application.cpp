#include <ere/core/application.hpp>
#include <iostream>

namespace ere {

application::application(const windowAPI::windowProps& t_props) {
    m_windowAPI = windowAPI::createConcreteWindowAPI();
    m_windowAPI->setEventFunction(std::bind(&application::onEvent, this, std::placeholders::_1));
    m_windowAPI->createWindow(t_props);

    ref<imguiLayer> ilayer = createRef<imguiLayer>(); 
    m_imguiLayer = ilayer;
    pushOverlay(ilayer);
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

            // * send a window updated event
            updateEvent e(m_timer.getDeltaTime());
            m_windowAPI->sendEvent(e);

            // * imgui
            m_imguiLayer.lock()->begin(m_timer.getDeltaTime(), m_windowAPI->getWindowSize(), m_windowAPI->getWindowFramebufferSize());
            imguiUpdateEvent imguiEvent;
            m_windowAPI->sendEvent(imguiEvent);
            m_imguiLayer.lock()->end();

            m_windowAPI->postRender();
        }
    }
}

/* -- Layers -- */

void application::pushLayer(std::shared_ptr<iLayer> t_layer) {
    // * force an on attach event to the layer
    attachEvent e;
    t_layer->onEvent(e);

    // * push to layer stack
    m_layers.insert(m_layers.begin() + (m_layersEnd++), t_layer);
}

void application::pushOverlay(std::shared_ptr<iLayer> t_layer) {
    // * force an on attach event to the layer
    attachEvent e;
    t_layer->onEvent(e);

    // * push to layer stack
    m_layers.push_back(t_layer);
}

void application::removeLayer(std::shared_ptr<iLayer> t_layer) {
    // * find the layer
    auto it = std::find(m_layers.begin(), m_layers.begin() + m_layersEnd, t_layer);
    // * check if layuer found
    if (it != m_layers.begin() + m_layersEnd) {
        // * force an on detach event
        detachEvent e;
        t_layer->onEvent(e);
        // * erease from layer stack
        m_layers.erase(it);
        // * decremnt the overlay start pos
        m_layersEnd--;
    }
}

void application::removeOverlay(std::shared_ptr<iLayer> t_layer) {
    // * find the overlay
    auto it = std::find(m_layers.begin() + m_layersEnd, m_layers.end(), t_layer);
    // * check it was found
    if (it != m_layers.end()) {
        // * force a detach event
        detachEvent e;
        t_layer->onEvent(e);
        // * remove the layer
        m_layers.erase(it);
    }
}

/* -- Events -- */

void application::onEvent(ereEvent& t_event) {
    // * dispatch a window closed event to stop the application loop
    util::event_dispatcher<ereEvents> dispatcher(t_event);
    dispatcher.dispatch<windowClosedEvent>(std::bind(&application::onWindowClose, this, std::placeholders::_1));

    // * propagate events down the event stack
    for (auto it = m_layers.end(); it != m_layers.begin();) {
        (*--it)->onEvent(t_event);

        if (t_event.handled()) {
            break;
        }
    }
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



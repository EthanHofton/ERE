#include <ere/core/application.hpp>

namespace ere {

ref<application> application::create_application() {
    return createRef<application>();
}

application::application() {
    ERE_INFO("Application created");

    m_window_driver = window_api::create_concrete();
    m_window_driver->set_event_callback(std::bind(&application::on_event, this, std::placeholders::_1));
    m_window_driver->create_window({"ere engine", 1280, 720});
}

application::~application() {
    ERE_INFO("Application destroyed");

    m_window_driver->destroy_window();
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

            m_window_driver->pre_render();

            // send a window updated event
            update_event e_update(m_timer.getDeltaTime());
            on_event(e_update);

            // send a imgui updated event
            // imgui_update_event e_imgui_update;
            // on_event(e_imgui_update);

            m_window_driver->post_render();
        }
    }
}

void application::on_event(ere_event& t_e) {
    ERE_TRACE("Application event");

    // check if the event is a window close event
    util::event_dispatcher<ere_events> dispatcher(t_e);

    // disptach the event to the window close event, to stop the application from running if the window is closed
    dispatcher.dispatch<window_closed_event>([this](window_closed_event& t_e) {
        ERE_TRACE("Window closed event");
        m_running = false;
        return true;
    });

    // propagate the event to the layers
    for (auto it = m_layers.begin(); it != m_layers.end();) {
        // incrament and call the on event function
        (*--it)->on_event(t_e);

        // check if the event has been handled
        if (t_e.handled()) {
            // break if it has
            break;
        }
    }
}

void application::push_layer(ref<i_layer> t_layer) {
    ERE_TRACE("Pushing layer");

    // trigger an on attach event
    attach_event e;
    t_layer->on_event(e);

    // add the layer to the layer stack
    m_layers.insert(m_layers.begin() + (m_layersEnd++), t_layer);
}

void application::pop_layer(ref<i_layer> t_layer) {
    ERE_TRACE("Popping layer");

    // trigger an on detach event
    detach_event e;
    t_layer->on_event(e);

    // remove the layer from the layer stack
    m_layers.erase(std::remove(m_layers.begin(), m_layers.end(), t_layer), m_layers.end());

    // decrement the end of the layer stack
    m_layersEnd--;
}

void application::push_overlay(ref<i_layer> t_overlay) {
    ERE_TRACE("Pushing overlay");

    // trigger an on attach event
    attach_event e;
    t_overlay->on_event(e);

    // add the overlay to the layer stack
    m_layers.push_back(t_overlay);
}

void application::pop_overlay(ref<i_layer> t_overlay) {
    ERE_TRACE("Popping overlay");

    // trigger an on detach event
    detach_event e;
    t_overlay->on_event(e);

    // remove the layer from the layer stack
    m_layers.erase(std::remove(m_layers.begin(), m_layers.end(), t_overlay), m_layers.end());
}

}

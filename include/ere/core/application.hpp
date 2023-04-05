#ifndef __ERE_APPLICATION_HPP__
#define __ERE_APPLICATION_HPP__

#include <util/timer.hpp>
#include <ere/events/events.hpp>
#include <ere/events/window_events.hpp>
#include <ere/events/app_events.hpp>
#include <ere/api/window_api.hpp>
#include <ere/imgui/imgui_layer.hpp>

#include "i_layer.hpp"

#include "logger.hpp"
#include "core.hpp"

namespace ere {

class application {
public:

    /**
    * @brief create an application
    *
    * @return ref<application> the application
    */
    static ref<application> create_application();

    /**
    * @brief Construct a new application object
    */
    application();
    /**
    * @brief Destroy the application object
    */
    ~application();

    /**
    * @brief run the application
    */
    void run();

    /**
    * @brief on event
    */
    void on_event(ere_event& t_e);

    /**
    * @brief set the fps
    *
    * @param fps the fps
    */
    inline void set_fps(double fps) { m_fps = fps; }

    /* -- layer stack -- */
    /**
    * @brief push a layer to the layer stack
    *
    * @param layer the layer
    */
    void push_layer(ref<i_layer> t_layer);
    /**
    * @brief push an overlay to the layer stack
    *
    * @param overlay the overlay
    */
    void push_overlay(ref<i_layer> t_overlay);
    /**
    * @brief pop a layer from the layer stack
    *
    * @param layer the layer
    */
    void pop_layer(ref<i_layer> t_layer);
    /**
    * @brief pop an overlay from the layer stack
    *
    * @param overlay the overlay
    */
    void pop_overlay(ref<i_layer> t_overlay);

    /**
    * @brief manually kill the application
    */
    inline void stop() { m_running = false; }
    

private:

    ref<window_api> m_window_driver;

    std::vector<ref<i_layer>> m_layers;
    unsigned int m_layersEnd = 0;

    double m_fps = 60.0;
    bool m_running = true;
    util::manual_timer m_timer;

    ref<imgui_layer> m_imgui_layer;
};

}

#endif

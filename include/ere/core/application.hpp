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
private:

    /**
    * @brief Construct a new application object
    */
    application();

    /**
    * @brief static instance to the application
    */
    static ref<application> s_instance;

public:

    /**
    * @brief create an application
    *
    * @return ref<application> the application
    */
    static ref<application> get_application();

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

    /* ==== window api methods ==== */
    inline void set_window_size(const glm::vec2& t_size) { m_window_driver->set_window_size(t_size); }
    inline void set_window_pos(const glm::vec2& t_pos) { m_window_driver->set_window_pos(t_pos); }
    inline void set_window_title(const std::string& t_title) { m_window_driver->set_window_title(t_title); }
    inline void set_window_swap_interval(int t_interval) { m_window_driver->set_window_swap_interval(t_interval); }

    inline glm::vec2 get_window_size() const { return m_window_driver->get_window_size(); }
    inline glm::vec2 get_window_pos() const { return m_window_driver->get_window_pos(); }
    inline glm::vec2 get_window_framebuffer_size() const { return m_window_driver->get_window_framebuffer_size(); }

    inline void maximize_window() { m_window_driver->maximize_window(); }
    inline void minimize_window() { m_window_driver->minimize_window(); }
    inline void restore_window() { m_window_driver->restore_window(); }
    inline void focus_window() { m_window_driver->focus_window(); }

    inline void set_background_color(const glm::vec4& t_color) { m_window_driver->set_background_color(t_color); }
    inline glm::vec4 get_background_color() const { return m_window_driver->get_background_color(); }

    inline void set_relative_mouse_mode(bool t_relative) { m_window_driver->set_relative_mouse_mode(t_relative); }
    inline void vsync(bool t_vsync) { m_window_driver->set_window_swap_interval(t_vsync); }

    inline double get_delta_time() { return m_timer.getDeltaTime(); }

    inline bool is_key_pressed(int t_key) { return m_window_driver->is_key_pressed(t_key); }
    inline bool is_key_released(int t_key) { return m_window_driver->is_key_released(t_key); }
    inline bool is_mouse_button_pressed(int t_button) { return m_window_driver->is_mouse_button_pressed(t_button); }
    inline bool is_mouse_button_released(int t_button) { return m_window_driver->is_mouse_button_released(t_button); }
    inline glm::vec2 get_mouse_pos() { return m_window_driver->get_mouse_pos(); }

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

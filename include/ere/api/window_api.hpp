#ifndef __ERE_WINDOW_API_HPP__
#define __ERE_WINDOW_API_HPP__

#include <functional>
#include <glm/glm.hpp>
#include <ere/events/window_events.hpp>
#include <ere/events/key_events.hpp>
#include <ere/events/mouse_events.hpp>
#include <ere/core/core.hpp>

namespace ere {
    
class window_api {
public:

    using event_callback_fn = std::function<void(ere_event&)>;
    struct window_props {
        std::string title;
        unsigned int width;
        unsigned int height;

        window_props(const std::string& title = "ere engine",
                     unsigned int width = 1280,
                     unsigned int height = 720)
            : title(title), width(width), height(height) {}
    };

    struct driver_data {
        glm::vec2 m_last_mouse_pos;
        bool m_first_mouse_move;
        event_callback_fn m_fn = [](ere_event& e){};
    };

    static ref<window_api> create_concrete();

    virtual ~window_api() = default;
    virtual void create_window(const window_props& t_props) = 0;
    virtual void destroy_window() = 0;

    virtual void set_window_size(const glm::vec2& t_size) = 0;
    virtual void set_window_pos(const glm::vec2& t_pos) = 0;
    virtual void set_window_title(const std::string& t_title) = 0;
    virtual void set_window_swap_interval(int t_interval) = 0;

    virtual glm::vec2 get_window_size() const = 0;
    virtual glm::vec2 get_window_pos() const = 0;
    virtual glm::vec2 get_window_framebuffer_size() const = 0;

    virtual void maximize_window() = 0;
    virtual void minimize_window() = 0;
    virtual void restore_window() = 0;
    virtual void focus_window() = 0;

    virtual void pre_render() = 0;
    virtual void post_render() = 0;

    virtual void set_background_color(const glm::vec4& t_color) = 0;
    virtual glm::vec4 get_background_color() const = 0;

    virtual void set_relative_mouse_mode(bool t_relative) = 0;

    inline void set_event_callback(event_callback_fn t_fn) { m_driver_data.m_fn = t_fn; }

    // key inputs
    virtual bool is_key_pressed(int t_key) const = 0;
    virtual bool is_key_released(int t_key) const = 0;
    virtual bool is_mouse_button_pressed(int t_button) const = 0;
    virtual bool is_mouse_button_released(int t_button) const = 0;
    virtual glm::vec2 get_mouse_pos() const = 0;

protected:

    driver_data m_driver_data;

};

}

#endif

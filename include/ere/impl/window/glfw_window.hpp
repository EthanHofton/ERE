#ifndef __ERE_GLFW_WINDOW_HPP__
#define __ERE_GLFW_WINDOW_HPP__

#include <ere/api/window_api.hpp>
#include <ere/ere_config.hpp>

#ifdef USE_GLFW

#ifdef USE_OPENGL
// glad must be included before glfw
#include <glad/glad.h>
#endif

#include <ere/api/render_api.hpp>
#include <GLFW/glfw3.h>
#include <ere/core/logger.hpp>

namespace ere {

class glfw_window : public window_api {
public:
    ~glfw_window() override = default;

    void create_window(const window_props& t_props) override final;
    void destroy_window() override final;

    void set_window_size(const glm::vec2& t_size) override final;
    void set_window_pos(const glm::vec2& t_pos) override final;
    void set_window_title(const std::string& t_title) override final;
    void set_window_swap_interval(int t_interval) override final;

    glm::vec2 get_window_size() const override final;
    glm::vec2 get_window_pos() const override final;
    glm::vec2 get_window_framebuffer_size() const override final;

    void maximize_window() override final;
    void minimize_window() override final;
    void restore_window() override final;
    void focus_window() override final;

    void pre_render() override final;
    void post_render() override final;

    void set_relative_mouse_mode(bool t_relative) override final;

    void set_background_color(const glm::vec4& t_color) override final;
    glm::vec4 get_background_color() const override final;

    bool is_key_pressed(int t_key) const override final;
    bool is_key_released(int t_key) const override final;
    bool is_mouse_button_pressed(int t_button) const override final;
    bool is_mouse_button_released(int t_button) const override final;
    glm::vec2 get_mouse_pos() const override final;

private:

    GLFWwindow* m_window;
    glm::vec4 m_background_color = {1.f, 1.f, 1.f, 1.f};
};

}

#endif

#endif

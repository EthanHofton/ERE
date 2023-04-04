#include <ere/impl/window/glfw_window.hpp>

#ifdef USE_GLFW

namespace ere {

ref<window_api> window_api::create_concrete() {
    return createRef<glfw_window>();
}

void glfw_window::create_window(const window_props &t_props) {
    /* -- GLFW setup -- */
    ERE_INFO("Initalizing GLFW");
    if (!glfwInit()) {
        ERE_CRITICAL("GLFW initalization failed");
        throw std::runtime_error("glfw initalization failed");
    }

    ERE_INFO("Creating window...");
    m_window = glfwCreateWindow(t_props.width, t_props.height, t_props.title.c_str(), NULL, NULL);

    if (m_window == nullptr) {
        glfwTerminate();
        ERE_CRITICAL("Failed to create window");
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(m_window);

    // renderer init
    // render_api::init();
    // render_api::set_viewport(0, 0, t_props.width, t_props.height);

    /* -- GLFW callbacks -- */
    // set the user pointer
    glfwSetWindowUserPointer(m_window, &m_driver_data);

// * glfw framebuffer size callback
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* t_window, int t_w, int t_h) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);
        // render_api::set_viewport(0, 0, t_w, t_h);
        window_framebuffer_resized_event e({t_w, t_h});
        data.m_fn(e);
    });

    // * glfw error callback
    glfwSetErrorCallback([](int t_code, const char* t_msg) {
        ERE_ERROR("GLFW error ({}) with message: {}", t_code, t_msg);
    });

    // * glfw size callback
    glfwSetWindowSizeCallback(
    m_window, [](GLFWwindow *t_window, int t_width, int t_height) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);

        window_resized_event e({t_width, t_height});
        data.m_fn(e);
    });

    // * window closed
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow *t_window) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);

        window_closed_event e;
        data.m_fn(e);
    });

    // * window moved
    glfwSetWindowPosCallback(
    m_window, [](GLFWwindow *t_window, int t_x, int t_y) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);

        window_moved_event e({t_x, t_y});
        data.m_fn(e);
    });

    // * window focus
    glfwSetWindowFocusCallback(m_window, [](GLFWwindow *t_window, int t_focused) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);

        if (t_focused) {
            // * window moved into focus
            window_focus_event e;
            data.m_fn(e);
        } else {
            // * window moved out of focus
            window_lost_focus_event e;
            data.m_fn(e);
        }
    });

    // * window maximized/restored
    glfwSetWindowMaximizeCallback(
    m_window, [](GLFWwindow *t_window, int t_maximized) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);

        if (t_maximized) {
            // * window maximized
            window_maximized_event e;
            data.m_fn(e);
        } else {
            // * window restored
            window_restored_event e;
            data.m_fn(e);
        }
    });

    // * window minimize/restore
    glfwSetWindowIconifyCallback(
    m_window, [](GLFWwindow *t_window, int t_iconified) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);

        if (t_iconified) {
            // * window maximized
            window_minimized_event e;
            data.m_fn(e);
        } else {
            // * window restored
            window_restored_event e;
            data.m_fn(e);
        }
    });

    // * window key events
    glfwSetKeyCallback(m_window, [](GLFWwindow *t_window, int t_key,
    int t_scancode, int t_action, int t_mods) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);
        switch (t_action) {
            case GLFW_PRESS: {
                key_pressed_event e(t_key, 0);
                data.m_fn(e);
                break;
            }
            case GLFW_RELEASE: {
                key_released_event e(t_key);
                data.m_fn(e);
                break;
            }
            case GLFW_REPEAT: {
                key_pressed_event e(t_key, 1);
                data.m_fn(e);
                break;
            }
        }
    });

    // * window key typed
    glfwSetCharCallback(m_window, [](GLFWwindow *t_window, unsigned int t_char) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);
        key_typed_event e(t_char);
        data.m_fn(e);
    });

    // * window mouse pressed callbacks
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *t_window, int t_button, int t_action, int t_mods) {
        driver_data &data = *(driver_data *)glfwGetWindowUserPointer(t_window);
        switch (t_action) {
            case GLFW_PRESS: {
                mouse_button_pressed_event e(t_button);
                data.m_fn(e);
                break;
            }
            case GLFW_RELEASE: {
                mouse_button_released_event e(t_button);
                data.m_fn(e);
                break;
            }
        }
    });

    // * window mouse scrolled
    glfwSetScrollCallback(m_window, [](GLFWwindow *t_window, double t_x, double t_y) {
        driver_data &wdata = *(driver_data*)glfwGetWindowUserPointer(t_window);
        mouse_scrolled_event e({t_x, t_y});
        wdata.m_fn(e);
    });


    // * mouse moved callback
    glfwSetCursorPosCallback(m_window, [](GLFWwindow *t_window, double t_x, double t_y) {
        driver_data &wdata = *(driver_data*)glfwGetWindowUserPointer(t_window);
        if (wdata.m_first_mouse_move)
        {
            wdata.m_last_mouse_pos = {t_x, t_y};
            wdata.m_first_mouse_move = false;
        }

        glm::vec2 mousePosOffset = {t_x - wdata.m_last_mouse_pos.x, wdata.m_last_mouse_pos.y - t_y};
        wdata.m_last_mouse_pos = {t_x, t_y};

        // * create a mouse scroll event
        mouse_moved_event event({t_x, t_y}, mousePosOffset);
        // * run the window event callback function with the created event
        wdata.m_fn(event);
    });
}

void glfw_window::destroy_window() {
    ERE_INFO("Destroying GLFW window");
    glfwDestroyWindow(m_window);
    ERE_INFO("Terminating GLFW");
    glfwTerminate();
}

void glfw_window::set_window_size(const glm::vec2& t_size) { glfwSetWindowSize(m_window, t_size.x, t_size.y); }
void glfw_window::set_window_pos(const glm::vec2& t_pos) { glfwSetWindowPos(m_window, t_pos.x, t_pos.y); }
void glfw_window::set_window_title(const std::string& t_title) { glfwSetWindowTitle(m_window, t_title.c_str()); }
void glfw_window::set_window_swap_interval(int t_fps) { glfwSwapInterval(t_fps); }
glm::vec2 glfw_window::get_window_size() const {
    glm::ivec2 size;
    glfwGetWindowSize(m_window, &size.x, &size.y);
    return size;
}
glm::vec2 glfw_window::get_window_framebuffer_size() const {
    glm::ivec2 size;
    glfwGetFramebufferSize(m_window, &size.x, &size.y);
    return size;
}
glm::vec2 glfw_window::get_window_pos() const {
    glm::ivec2 size;
    glfwGetWindowPos(m_window, &size.x, &size.y);
    return size;
}
void glfw_window::maximize_window() { glfwMaximizeWindow(m_window); }
void glfw_window::minimize_window() { glfwIconifyWindow(m_window); }
void glfw_window::restore_window() { glfwRestoreWindow(m_window); }
void glfw_window::focus_window() { glfwFocusWindow(m_window); }
void glfw_window::pre_render() {
    // render_api::clear_color(m_background_color);
    // render_api::clear_buffer();
}
void glfw_window::post_render() { glfwSwapBuffers(m_window); glfwPollEvents(); }
void glfw_window::set_background_color(const glm::vec4& t_color) { m_background_color = t_color; }
glm::vec4 glfw_window::get_background_color() const { return m_background_color; }

}


#endif

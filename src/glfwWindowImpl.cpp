#include <ere/impl/glfwWindowImpl.hpp>

#if defined(USE_GLFW)

namespace ere {

ref<windowAPI> windowAPI::createConcreteWindowAPI() {
    // * return a shared pointer for windowAPI class, created with glfwWindowImpl
    return createRef<glfwWindowImpl>();
}

void glfwWindowImpl::createWindow(const windowProps& t_props) {
    /* -- GLFW setup -- */
    ERE_INFO("Initalizing GLFW");
    if (!glfwInit()) {
        ERE_CRITICAL("GLFW initalization failed");
        throw std::runtime_error("glfw initalization failed");
    }

    #ifdef USE_OPENGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif
    
    ERE_INFO("Creating window...");
    m_window = glfwCreateWindow(t_props.m_width, t_props.m_height, t_props.m_title.c_str(), NULL, NULL);

    if (m_window == nullptr) {
        glfwTerminate();
        ERE_CRITICAL("Failed to create window");
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(m_window);

    #ifdef USE_OPENGL
    // * initalize glad
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        ERE_CRITICAL("Failed to initalize GLAD");
        throw std::runtime_error("Failed to initalize GLAD");
    }

    // * set viewport 
    glViewport(0, 0, t_props.m_width, t_props.m_height);
    #endif

    /* -- GLFW callbacks -- */
    glfwSetWindowUserPointer(m_window, &m_driverData);

    // * glfw framebuffer size callback
    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* t_window, int t_w, int t_h) {
        #ifdef USE_OPENGL
        glViewport(0, 0, t_w, t_h);
        #endif
    });

    // * glfw error callback
    glfwSetErrorCallback([](int t_code, const char* t_msg) {
        ERE_ERROR("GLFW error ({}) with message: {}", t_code, t_msg);
    });

    // * glfw size callback
    glfwSetWindowSizeCallback(
    m_window, [](GLFWwindow *t_window, int t_width, int t_height) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);

        windowResizeEvent e({t_width, t_height});
        data.m_eventFn(e);
    });

    // * window closed
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow *t_window) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);

        windowClosedEvent e;
        data.m_eventFn(e);
    });

    // * window moved
    glfwSetWindowPosCallback(
    m_window, [](GLFWwindow *t_window, int t_x, int t_y) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);

        windowMovedEvent e({t_x, t_y});
        data.m_eventFn(e);
    });

    // * window focus
    glfwSetWindowFocusCallback(m_window, [](GLFWwindow *t_window, int t_focused) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);

        if (t_focused) {
            // * window moved into focus
            windowFocusEvent e;
            data.m_eventFn(e);
        } else {
            // * window moved out of focus
            windowLostFocusEvent e;
            data.m_eventFn(e);
        }
    });

    // * window maximized/restored
    glfwSetWindowMaximizeCallback(
    m_window, [](GLFWwindow *t_window, int t_maximized) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);

        if (t_maximized) {
            // * window maximized
            windowMaximisedEvent e;
            data.m_eventFn(e);
        } else {
            // * window restored
            windowRestoredEvent e;
            data.m_eventFn(e);
        }
    });

    // * window minimize/restore
    glfwSetWindowIconifyCallback(
    m_window, [](GLFWwindow *t_window, int t_iconified) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);

        if (t_iconified) {
            // * window maximized
            windowMinimizedEvent e;
            data.m_eventFn(e);
        } else {
            // * window restored
            windowRestoredEvent e;
            data.m_eventFn(e);
        }
    });

    // * window key events
    glfwSetKeyCallback(m_window, [](GLFWwindow *t_window, int t_key,
    int t_scancode, int t_action, int t_mods) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);
        switch (t_action) {
            case GLFW_PRESS: {
                keyPressedEvent e(t_key, 0);
                data.m_eventFn(e);
                break;
            }
            case GLFW_RELEASE: {
                keyReleasedEvent e(t_key);
                data.m_eventFn(e);
                break;
            }
            case GLFW_REPEAT: {
                keyPressedEvent e(t_key, 1);
                data.m_eventFn(e);
                break;
            }
        }
    });

    // * window key typed
    glfwSetCharCallback(m_window, [](GLFWwindow *t_window, unsigned int t_char) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);
        keyTypedEvent e(t_char);
        data.m_eventFn(e);
    });

    // * window mouse pressed callbacks
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow *t_window, int t_button, int t_action, int t_mods) {
        driverData &data = *(driverData *)glfwGetWindowUserPointer(t_window);
        switch (t_action) {
            case GLFW_PRESS: {
                mouseButtonPressedEvent e(t_button);
                data.m_eventFn(e);
                break;
            }
            case GLFW_RELEASE: {
                mouseButtonReleasedEvent e(t_button);
                data.m_eventFn(e);
                break;
            }
        }
    });

    // * window mouse scrolled
    glfwSetScrollCallback(m_window, [](GLFWwindow *t_window, double t_x, double t_y) {
        driverData &wdata = *(driverData*)glfwGetWindowUserPointer(t_window);
        mouseScrolledEvent e({t_x, t_y});
        wdata.m_eventFn(e);
    });


    // * mouse moved callback
    glfwSetCursorPosCallback(m_window, [](GLFWwindow *t_window, double t_x, double t_y) {
        driverData &wdata = *(driverData*)glfwGetWindowUserPointer(t_window);
        if (wdata.m_firstMouseMove)
        {
            wdata.m_lastMousePos = {t_x, t_y};
            wdata.m_firstMouseMove = false;
        }

        glm::vec2 mousePosOffset = {t_x - wdata.m_lastMousePos.x, wdata.m_lastMousePos.y - t_y};
        wdata.m_lastMousePos = {t_x, t_y};

        // * create a mouse scroll event
        mouseMovedEvent event({t_x, t_y}, mousePosOffset);
        // * run the window event callback function with the created event
        wdata.m_eventFn(event);
    });
}

void glfwWindowImpl::destroyWindow() {
    ERE_INFO("Destroying window...");
    glfwDestroyWindow(m_window);
    ERE_INFO("Terminating GLFW");
    glfwTerminate();
}

void glfwWindowImpl::setWindowSize(const glm::vec2& t_size) { glfwSetWindowSize(m_window, t_size.x, t_size.y); }
void glfwWindowImpl::setWindowPos(const glm::vec2& t_pos) { glfwSetWindowPos(m_window, t_pos.x, t_pos.y); }
void glfwWindowImpl::setWindowTitle(const std::string& t_title) { glfwSetWindowTitle(m_window, t_title.c_str()); }
void glfwWindowImpl::setWindowSwapInterval(const int& t_fps) { glfwSwapInterval(t_fps); }
glm::vec2 glfwWindowImpl::getWindowSize() const {
    glm::ivec2 size;
    glfwGetWindowSize(m_window, &size.x, &size.y);
    return size;
}
glm::vec2 glfwWindowImpl::getWindowPos() const {
    glm::ivec2 size;
    glfwGetWindowPos(m_window, &size.x, &size.y);
    return size;
}
void glfwWindowImpl::maximizeWindow() { glfwMaximizeWindow(m_window); }
void glfwWindowImpl::minimizeWindow() { glfwIconifyWindow(m_window); }
void glfwWindowImpl::restoreWindow() { glfwRestoreWindow(m_window); }
void glfwWindowImpl::focusWindow() { glfwFocusWindow(m_window); }
void glfwWindowImpl::preRender() {
    #ifdef USE_OPENGL
    glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    #endif
}
void glfwWindowImpl::postRender() { glfwSwapBuffers(m_window); glfwPollEvents(); }
void glfwWindowImpl::setBackgroundColor(const glm::vec4& t_color) { m_backgroundColor = t_color; }

}

#endif

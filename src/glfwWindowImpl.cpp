#include <ere/impl/glfwWindowImpl.hpp>

#if defined(USE_GLFW)

namespace ere {

std::shared_ptr<windowAPI> windowAPI::createConcreteWindowAPI() {
    // * return a shared pointer for windowAPI class, created with glfwWindowImpl
    return std::make_shared<glfwWindowImpl>();
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
    // * load glad
    gladLoadGL(glfwGetProcAddress);

    // * set viewport 
    glViewport(0, 0, t_props.t_width, t_props.t_height);
    #endif

    /* -- GLFW callbacks -- */

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

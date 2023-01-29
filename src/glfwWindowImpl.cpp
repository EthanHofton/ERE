#include <ere/impl/glfwWindowImpl.hpp>

#if defined(USE_GLFW)

namespace ere {

std::shared_ptr<windowAPI> windowAPI::createConcreteWindowAPI() {
    // * return a shared pointer for windowAPI class, created with glfwWindowImpl
    return std::make_shared<glfwWindowImpl>();
}

void glfwWindowImpl::createWindow(const windowProps& t_props) {}
void glfwWindowImpl::destroyWindow() {}

void glfwWindowImpl::setWindowSize(const glm::vec2& t_size) {}
void glfwWindowImpl::setWindowPos(const glm::vec2& t_pos) {}
void glfwWindowImpl::setWindowTitle(const std::string& t_title) {}
void glfwWindowImpl::setWindowSwapInterval(const int& t_fps) {}
glm::vec2 glfwWindowImpl::getWindowSize() {}
glm::vec2 glfwWindowImpl::getWindowPos() {}
void glfwWindowImpl::maximizeWindow() {}
void glfwWindowImpl::minimizeWindow() {}
void glfwWindowImpl::restoreWindow() {}
void glfwWindowImpl::focusWindow() {}

}

#endif

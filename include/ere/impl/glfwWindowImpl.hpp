#ifndef ERE_IMPL_GLFW_WINDOW_IMPL_HPP
#define ERE_IMPL_GLFW_WINDOW_IMPL_HPP

#include <ere/api/windowAPI.hpp>
#include <ereConfig.hpp>

#if defined(USE_GLFW)

namespace ere {

class glfwWindowImpl : public windowAPI {
    virtual void createWindow(const windowProps& t_props);
    virtual void destroyWindow();

    virtual void setWindowSize(const glm::vec2& t_size);
    virtual void setWindowPos(const glm::vec2& t_pos);
    virtual void setWindowTitle(const std::string& t_title);
    virtual void setWindowSwapInterval(const int& t_fps);
    virtual glm::vec2 getWindowSize();
    virtual glm::vec2 getWindowPos();
    virtual void maximizeWindow();
    virtual void minimizeWindow();
    virtual void restoreWindow();
    virtual void focusWindow();
};

}

#endif

#endif

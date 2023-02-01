#ifndef ERE_IMPL_GLFW_WINDOW_IMPL_HPP
#define ERE_IMPL_GLFW_WINDOW_IMPL_HPP

#include <ere/api/windowAPI.hpp>
#include <ereConfig.hpp>

#if defined(USE_GLFW)

#ifdef USE_OPENGL
// * include gl.h BEFORE glfw3.h
#include <glad/gl.h>
#endif

#include <GLFW/glfw3.h>
#include <ere/core/logger.hpp>

namespace ere {

class glfwWindowImpl : public windowAPI {
    virtual void createWindow(const windowProps& t_props);
    virtual void destroyWindow();

    virtual void setWindowSize(const glm::vec2& t_size);
    virtual void setWindowPos(const glm::vec2& t_pos);
    virtual void setWindowTitle(const std::string& t_title);
    virtual void setWindowSwapInterval(const int& t_fps);
    virtual glm::vec2 getWindowSize() const;
    virtual glm::vec2 getWindowPos() const;
    virtual void maximizeWindow();
    virtual void minimizeWindow();
    virtual void restoreWindow();
    virtual void focusWindow();
    virtual void preRender();
    virtual void postRender();
    virtual void setBackgroundColor(const glm::vec4& t_color);

private:

    GLFWwindow *m_window = nullptr;
    glm::vec4 m_backgroundColor = {1.0f, 1.0f, 1.0f, 1.0f};
};

}

#endif

#endif

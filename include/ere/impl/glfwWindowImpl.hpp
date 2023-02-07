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
    virtual void createWindow(const windowProps& t_props) override;
    virtual void destroyWindow() override;

    virtual void setWindowSize(const glm::vec2& t_size) override;
    virtual void setWindowPos(const glm::vec2& t_pos) override;
    virtual void setWindowTitle(const std::string& t_title) override;
    virtual void setWindowSwapInterval(const int& t_fps) override;
    virtual glm::vec2 getWindowSize() const override;
    virtual glm::vec2 getWindowFramebufferSize() const override;
    virtual glm::vec2 getWindowPos() const override;
    virtual void maximizeWindow() override;
    virtual void minimizeWindow() override;
    virtual void restoreWindow() override;
    virtual void focusWindow() override;
    virtual void preRender() override;
    virtual void postRender() override;
    virtual void setBackgroundColor(const glm::vec4& t_color) override;

private:

    GLFWwindow *m_window = nullptr;
    glm::vec4 m_backgroundColor = {1.0f, 1.0f, 1.0f, 1.0f};
};

}

#endif

#endif

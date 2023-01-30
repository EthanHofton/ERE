#ifndef ERE_CORE_APPLICATION_HPP
#define ERE_CORE_APPLICATION_HPP

#include <vector>
#include <util/timer.hpp>
#include <ere/api/windowAPI.hpp>
#include <ere/events/appEvents.hpp>

#include "iLayer.hpp"

namespace ere {

class application {
public:

    application(const windowAPI::windowProps& t_props);
    ~application();

    void run();
    void onEvent(ereEvent& t_event);

    inline void setFPS(double t_fps) { m_fps = t_fps; }

    /* layer stack */
    void pushLayer(std::shared_ptr<iLayer> t_layer);
    void pushOverlay(std::shared_ptr<iLayer> t_layer);
    void removeLayer(std::shared_ptr<iLayer> t_layer);
    void removeOverlay(std::shared_ptr<iLayer> t_layer);

    /* -- windowAPI -- */
    void setWindowSize(const glm::vec2& t_size);
    void setWindowPos(const glm::vec2& t_pos);
    void setWindowTitle(const std::string& t_title);
    void setWindowSwapInterval(const int& t_swap);
    void setBackgroundColor(const glm::vec4& t_color);

    glm::vec2 getWindowSize() const;
    glm::vec2 getWindowPos() const;

    void maximiseWindow();
    void minimizeWindow();
    void restoreWindow();
    void focusWindow();

private:

    bool onWindowClose(windowClosedEvent& t_event);

private:

    std::vector<std::shared_ptr<iLayer>> m_layers;

    util::manual_timer m_timer;
    std::shared_ptr<windowAPI> m_windowAPI;
    bool m_running = true;
    double m_fps = 60.0f;

};

}

#endif

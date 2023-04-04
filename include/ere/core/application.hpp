#ifndef __ERE_APPLICATION_HPP__
#define __ERE_APPLICATION_HPP__

#include <util/timer.hpp>
#include <ere/events/events.hpp>
#include <ere/events/window_events.hpp>

#include "logger.hpp"
#include "core.hpp"

namespace ere {

class application {
public:

    /**
    * @brief create an application
    *
    * @return ref<application> the application
    */
    static ref<application> create_application();

    /**
    * @brief Construct a new application object
    */
    application();
    /**
    * @brief Destroy the application object
    */
    ~application();

    /**
    * @brief run the application
    */
    void run();

    /**
    * @brief on event
    */
    void on_event(ere_event& t_e);

    /**
    * @brief set the fps
    *
    * @param fps the fps
    */
    inline void set_fps(double fps) { m_fps = fps; }
    

private:

    double m_fps = 60.0;
    bool m_running = true;
    util::manual_timer m_timer;
};

}

#endif

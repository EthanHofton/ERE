#ifndef __ERE_APP_EVENTS_HPP__
#define __ERE_APP_EVENTS_HPP__

/* -- APPLICATION EVENTS: -- */
/* -- update, attach, detach -- */ 

#include "events.hpp"

namespace ere {

/**
* @brief update event
*/
class update_event : public ere_event {
public:

    /**
    * @brief Construct a new update event object
    *
    * @param t_deltaTime time since last update
    */
    inline update_event(const double& t_deltaTime) : m_deltaTime(t_deltaTime) {}

    /**
    * @brief Get the delta time object
    *
    * @return double time since last update
    */
    inline double get_delta_time() const { return m_deltaTime; }

    EVENT_CLASS_TYPE(ere::ere_events, update)

private:

    double m_deltaTime;
};

/**
* @brief attach event
*/
class attach_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere::ere_events, attach)
};

/**
* @brief detach event
*/
class detach_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere::ere_events, detach)
};

/**
* @brief imgui update event
*/
class imgui_update_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere::ere_events, imgui_update)
};

}

#endif

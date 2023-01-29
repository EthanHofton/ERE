#ifndef ERE_EVENTS_APP_EVENTS_HPP
#define ERE_EVENTS_APP_EVENTS_HPP

/* -- APPLICATION EVENTS: -- */
/* -- update, attach, detach -- */ 

#include "events.hpp"

namespace ere {
    
class updateEvent : public ereEvent {
public:

    updateEvent(const double& t_deltaTime) : m_deltaTime(t_deltaTime) {}

    double getDeltaTime() const { return m_deltaTime; }

    EVENT_CLASS_TYPE(ere::ereEvents, update)

private:

    double m_deltaTime;
};

class attachEvent : public ereEvent {
public:

    EVENT_CLASS_TYPE(ere::ereEvents, attach)
};

class detachEvent : public ereEvent {
public:

    EVENT_CLASS_TYPE(ere::ereEvents, detach)
};

};

#endif

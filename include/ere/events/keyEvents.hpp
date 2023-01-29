#ifndef ERE_EVENTS_KEY_EVENTS_HPP
#define ERE_EVENTS_KEY_EVENTS_HPP

/* -- KEY EVENTS: -- */
/* -- keyPressed, keyReleased -- */ 

#include <sstream>
#include "events.hpp"

namespace ere {

class keyEvent : public ereEvent {
public:

    inline int getKeyCode() const { return m_keycode; }
    
protected:

    keyEvent(const int& t_keycode) : m_keycode(t_keycode) {}

    int m_keycode;
};

class keyPressedEvent : public keyEvent {
public:

    keyPressedEvent(int t_keycode, int t_repeteCount) : keyEvent(t_keycode), m_repeteCount(t_repeteCount) {}

    inline int getRepeteCount() const { return m_repeteCount; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeteCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere::ereEvents, keyPressed)

private:

    int m_repeteCount;
};

class keyReleasedEvent : public keyEvent
{
public:

    keyReleasedEvent(int t_keycode) : keyEvent(t_keycode) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere::ereEvents, keyReleased);
};

class keyTypedEvent : public keyEvent
{
public:

    keyTypedEvent(int t_keycode) : keyEvent(t_keycode) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(ereEvents, keyTyped);
};

}

#endif

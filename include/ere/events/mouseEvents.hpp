#ifndef ERE_EVENTS_MOUSE_EVENTS_HPP
#define ERE_EVENTS_MOUSE_EVENTS_HPP

/* -- MOUSE EVENTS: -- */
/* -- mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScolled -- */ 

#include <sstream>
#include <glm/glm.hpp>
#include "events.hpp"

namespace ere {

class mouseMovedEvent : public ereEvent {
public:

    mouseMovedEvent(const glm::vec2& t_pos, const glm::vec2& t_dpos) : m_pos(t_pos), m_dpos(t_dpos) {}

    inline glm::vec2 getPos() const { return m_pos; }
    inline glm::vec2 getDeltaPos() const { return m_dpos; }

    inline std::string toString() const override {
        std::stringstream ss;
        ss << "mouseMovedEvent: {" << m_pos.x << ", " << m_pos.y << "}, {" << m_dpos.x << ", " << m_dpos.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ereEvents, mouseMoved)

private:

    glm::vec2 m_pos;
    glm::vec2 m_dpos;
};

class mouseScrolledEvent : public ereEvent {
public:

    mouseScrolledEvent(const glm::vec2& t_offset) : m_offset(t_offset) {}

    inline glm::vec2 getOffset() const { return m_offset; }

    inline std::string toString() const override {
        std::stringstream ss;
        ss << "mouseMovedEvent: {" << m_offset.x << ", " << m_offset.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ereEvents, mouseScrolled)

private:

    glm::vec2 m_offset;
};

class mouseButtonEvent : public ereEvent {
public:

    inline int getMouseButton() const { return m_button; }

protected:

    mouseButtonEvent(const int& t_button) : m_button(t_button) {}

    int m_button;
};

class mouseButtonPressedEvent : public mouseButtonEvent {
public:

    mouseButtonPressedEvent(const int& t_button) : mouseButtonEvent(t_button) {}

    inline std::string toString() const override {
        std::stringstream ss;
        ss << "mouseButtonReleasedEvent: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(ereEvents, mouseButtonPressed)
};

class mouseButtonReleasedEvent : public mouseButtonEvent {
public:

    mouseButtonReleasedEvent(const int& t_button) : mouseButtonEvent(t_button) {}

    inline std::string toString() const override {
        std::stringstream ss;
        ss << "mouseButtonReleasedEvent: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(ereEvents, mouseButtonReleased)
};

}

#endif

#ifndef ERE_EVENTS_WINDOW_EVENTS_HPP
#define ERE_EVENTS_WINDOW_EVENTS_HPP

/* -- WINDOW EVENTS: -- */
/* -- windowClosed, windowMoved, windowResize, windowFocus, windowLostFocus, windowMinimized, windowMaximised, windowRestored -- */ 

#include <glm/glm.hpp> 
#include <sstream>
#include "events.hpp"

namespace ere {

class windowClosedEvent : public ereEvent {
public:

    EVENT_CLASS_TYPE(ereEvents, windowClosed)
};

class windowMinimizedEvent : public ereEvent {
public:

    EVENT_CLASS_TYPE(ereEvents, windowMinimized)
};

class windowMaximisedEvent : public ereEvent {
public:

    EVENT_CLASS_TYPE(ereEvents, windowMaximised)
};

class windowRestoredEvent : public ereEvent {
public:

    EVENT_CLASS_TYPE(ereEvents, windowRestored)
};

class windowFocusEvent : public ereEvent {
public:

    EVENT_CLASS_TYPE(ereEvents, windowFocus)
};

class windowLostFocusEvent : public ereEvent {
public:

    EVENT_CLASS_TYPE(ereEvents, windowLostFocus)
};

class windowMovedEvent : public ereEvent {
public:

    windowMovedEvent(const glm::vec2& t_winPos) : m_windowPos(t_winPos) {}

    inline glm::vec2 getWindowPos() const { return m_windowPos; } 

    std::string toString() const override {
        std::stringstream ss;
        ss << "windowMovedEvent: " << "{" << m_windowPos.x << ", " << m_windowPos.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ereEvents, windowMoved)

private:

    glm::vec2 m_windowPos;
};

class windowResizeEvent : public ereEvent {
public:

    windowResizeEvent(const glm::vec2& t_size) : m_windowSize(t_size) {}

    inline glm::vec2 getWindowSize() const { return m_windowSize; } 

    std::string toString() const override {
        std::stringstream ss;
        ss << "windowResizeEvent: " << "{" << m_windowSize.x << ", " << m_windowSize.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ereEvents, windowResize)

private:

    glm::vec2 m_windowSize;
};

class windowFramebufferResizeEvent : public ereEvent {
public:

    windowFramebufferResizeEvent(const glm::vec2& t_size) : m_windowSize(t_size) {}

    inline glm::vec2 getWindowFramebufferSize() const { return m_windowSize; } 

    std::string toString() const override {
        std::stringstream ss;
        ss << "windowFramebufferResizeEvent: " << "{" << m_windowSize.x << ", " << m_windowSize.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ereEvents, windowResize)

private:

    glm::vec2 m_windowSize;
};

}

#endif

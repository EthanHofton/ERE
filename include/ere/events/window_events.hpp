#ifndef __ERE_WINDOW_EVENTS_HPP__
#define __ERE_WINDOW_EVENTS_HPP__

/* -- WINDOW EVENTS: -- */
/* -- windowClosed, windowMoved, windowResize, windowFocus, windowLostFocus, windowMinimized, windowMaximised, windowRestored -- */ 

#include <glm/glm.hpp> 
#include <sstream>
#include "events.hpp"

namespace ere {

/**
* @brief window closed event
*/
class window_closed_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere_events, window_closed)
};

/**
* @brief window minimized event
*/
class window_minimized_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere_events, window_minimized)
};

/**
* @brief window maximized event
*/
class window_maximized_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere_events, window_maximized)
};

/**
* @brief window restored event
*/
class window_restored_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere_events, window_restored)
};

/**
* @brief window focus event
*/
class window_focus_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere_events, window_focus)
};

/**
* @brief window lost focus event
*/
class window_lost_focus_event : public ere_event {
public:

    EVENT_CLASS_TYPE(ere_events, window_lost_focus)
};

/**
* @brief window moved event
*/
class window_moved_event : public ere_event {
public:

    /**
    * @brief Construct a new window moved event object
    *
    * @param t_winPos window position
    */
    inline window_moved_event(const glm::vec2& t_winPos) : m_windowPos(t_winPos) {}

    /**
    * @brief Get the window position
    *
    * @return 
    */
    inline glm::vec2 get_window_pos() const { return m_windowPos; } 

    /**
    * @brief Get the string representation of the event
    *
    * @return 
    */
    inline std::string toString() const override {
        std::stringstream ss;
        ss << "windowMovedEvent: " << "{" << m_windowPos.x << ", " << m_windowPos.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere_events, window_moved)

private:

    glm::vec2 m_windowPos;
};

/**
* @brief window resized event
*/
class window_resized_event : public ere_event {
public:

    /**
    * @brief Construct a new window resized event object
    *
    * @param t_size window size
    */
    inline window_resized_event(const glm::vec2& t_size) : m_windowSize(t_size) {}

    /**
    * @brief Get the window size
    *
    * @return the window size
    */
    inline glm::vec2 get_window_size() const { return m_windowSize; } 

    /**
    * @brief Get the string representation of the event
    *
    * @return the string representation of the event
    */
    inline std::string toString() const override {
        std::stringstream ss;
        ss << "windowResizeEvent: " << "{" << m_windowSize.x << ", " << m_windowSize.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere_events, window_resized)

private:

    glm::vec2 m_windowSize;
};

/**
* @brief window framebuffer resized event
*/
class window_framebuffer_resized_event : public ere_event {
public:

    /**
    * @brief Construct a new window framebuffer resized event object
    *
    * @param t_size window framebuffer size
    */
    inline window_framebuffer_resized_event(const glm::vec2& t_size) : m_windowSize(t_size) {}

    /**
    * @brief Get the window framebuffer size
    *
    * @return the window framebuffer size
    */
    inline glm::vec2 get_window_framebuffer_size() const { return m_windowSize; } 

    /**
    * @brief Get the string representation of the event
    *
    * @return 
    */
    inline std::string toString() const override {
        std::stringstream ss;
        ss << "windowFramebufferResizeEvent: " << "{" << m_windowSize.x << ", " << m_windowSize.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere_events, window_framebuffer_resized)

private:

    glm::vec2 m_windowSize;
};

}

#endif

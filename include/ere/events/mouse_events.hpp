#ifndef __ERE_MOUSE_EVENTS_HPP__
#define __ERE_MOUSE_EVENTS_HPP__

/* -- MOUSE EVENTS: -- */
/* -- mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScolled -- */ 

#include <sstream>
#include <glm/glm.hpp>

#include "events.hpp"

namespace ere {

/**
* @brief mouse event
*/
class mouse_moved_event : public ere_event {
public:

    /**
    * @brief Construct a new mouse moved event object
    *
    * @param t_pos current position
    * @param t_dpos delta position
    */
    inline mouse_moved_event(const glm::vec2& t_pos, const glm::vec2& t_dpos) : m_pos(t_pos), m_dpos(t_dpos) {}

    /**
    * @brief Get the position 
    *
    * @return glm::vec2 current position
    */
    inline glm::vec2 get_pos() const { return m_pos; }
    /**
    * @brief Get the delta position
    *
    * @return glm::vec2 delta position
    */
    inline glm::vec2 get_delta_pos() const { return m_dpos; }

    /**
    * @brief Get the string representation of the event
    *
    * @return std::string string representation of the event
    */
    inline std::string toString() const override {
        std::stringstream ss;
        ss << "mouseMovedEvent: {" << m_pos.x << ", " << m_pos.y << "}, {" << m_dpos.x << ", " << m_dpos.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere_events, mouse_moved)

private:

    glm::vec2 m_pos;
    glm::vec2 m_dpos;
};

/**
* @brief mouse scrolled event
*/
class mouse_scrolled_event : public ere_event {
public:

    /**
    * @brief Construct a new mouse scrolled event object
    *
    * @param t_offset offset
    */
    inline mouse_scrolled_event(const glm::vec2& t_offset) : m_offset(t_offset) {}

    /**
    * @brief Get the offset
    *
    * @return glm::vec2 offset
    */
    inline glm::vec2 get_offset() const { return m_offset; }

    /**
    * @brief Get the string representation of the event
    *
    * @return std::string string representation of the event
    */
    inline std::string toString() const override {
        std::stringstream ss;
        ss << "mouseMovedEvent: {" << m_offset.x << ", " << m_offset.y << "}";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere_events, mouse_scrolled)

private:

    glm::vec2 m_offset;
};

/**
* @brief mouse button event
*/
class mouse_button_event : public ere_event {
public:

    /**
    * @brief Get the mouse button
    *
    * @return int mouse button
    */
    inline int get_mouse_button() const { return m_button; }

protected:

    /**
    * @brief Construct a new mouse button event object
    *
    * @param t_button mouse button
    */
    inline mouse_button_event(const int& t_button) : m_button(t_button) {}

    /**
    * @brief mouse button
    */
    int m_button;
};

/**
* @brief mouse button pressed event
*/
class mouse_button_pressed_event : public mouse_button_event {
public:

    /**
    * @brief Construct a new mouse button pressed event object
    *
    * @param t_button mouse button
    */
    inline mouse_button_pressed_event(const int& t_button) : mouse_button_event(t_button) {}

    /**
    * @brief Get the string representation of the event
    *
    * @return std::string string representation of the event
    */
    inline std::string toString() const override {
        std::stringstream ss;
        ss << "mouseButtonReleasedEvent: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere_events, mouse_button_pressed)
};

/**
* @brief mouse button released event
*/
class mouse_button_released_event : public mouse_button_event {
public:

    /**
    * @brief Construct a new mouse button released event object
    *
    * @param t_button mouse button
    */
    inline mouse_button_released_event(const int& t_button) : mouse_button_event(t_button) {}

    /**
    * @brief Get the string representation of the event
    *
    * @return std::string string representation of the event
    */
    inline std::string toString() const override {
        std::stringstream ss;
        ss << "mouseButtonReleasedEvent: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere_events, mouse_button_released)
};

}

#endif

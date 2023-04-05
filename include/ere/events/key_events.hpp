#ifndef __ERE_KEY_EVENTS_HPP__
#define __ERE_KEY_EVENTS_HPP__

/* -- KEY EVENTS: -- */
/* -- keyPressed, keyReleased -- */ 

#include <sstream>
#include "events.hpp"

namespace ere {

/**
* @brief key event
*/
class key_event : public ere_event {
public:

    /**
    * @brief Get the key code object
    *
    * @return int key code
    */
    inline int get_key_code() const { return m_keycode; }
    
protected:

    /**
    * @brief Construct a new key event object
    *
    * @param t_keycode key code
    */
    inline key_event(const int& t_keycode) : m_keycode(t_keycode) {}

    /**
    * @brief key code
    */
    int m_keycode;
};

class key_pressed_event : public key_event {
public:

    /**
    * @brief Construct a new key pressed event object
    *
    * @param t_keycode key code
    * @param t_repeteCount number of times the key was pressed
    */
    inline key_pressed_event(int t_keycode, int t_repeteCount) : key_event(t_keycode), m_repeteCount(t_repeteCount) {}

    /**
    * @brief Get the repete count object
    *
    * @return int number of times the key was pressed
    */
    inline int get_repete_count() const { return m_repeteCount; }

    /**
    * @brief Get the string representation of the event
    *
    * @return std::string string representation of the event
    */
    inline std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeteCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere::ere_events, key_pressed)

private:

    int m_repeteCount;
};

/**
* @brief key released event
*/
class key_released_event : public key_event
{
public:

    /**
    * @brief Construct a new key released event object
    *
    * @param t_keycode key code
    */
    inline key_released_event(int t_keycode) : key_event(t_keycode) {}

    /**
    * @brief Get the string representation of the event
    *
    * @return std::string string representation of the event
    */
    inline std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere::ere_events, key_released);
};

/**
* @brief key typed event
*/
class key_typed_event : public key_event
{
public:

    /**
    * @brief Construct a new key typed event object
    *
    * @param t_keycode key code
    */
    inline key_typed_event(int t_keycode) : key_event(t_keycode) {}

    /**
    * @brief Get the string representation of the event
    *
    * @return std::string string representation of the event
    */
    inline std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(ere_events, key_typed);
};

}

#endif

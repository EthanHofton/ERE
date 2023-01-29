#ifndef ERE_API_WINDOW_API_HPP
#define ERE_API_WINDOW_API_HPP

#include <string>
#include <functional>
#include <memory>
#include <glm/glm.hpp>

namespace ere {

/**
* @brief an abstract windowAPI to be implamented using a specific windowing API (Cocoa, Vulkan, GLM, ...)
*/
class windowAPI {
public:

    /**
    * @brief forward declare windowProps
    */
    struct windowProps;
    // * TODO: create event handler
    // using eventCallbackFn = std::function<void util::event<>>;

    /**
    * @brief public access point for creating a window. each platform specitfic window will implament this API and implament the createWindow function
    * to return their version of a window
    *
    * @return a downcasted version of a concreate window impl
    */
    static std::shared_ptr<windowAPI> createConcreteWindowAPI();

    virtual ~windowAPI() = default;

    /* -- pure virtual functions -- */
    /**
    * @brief create a window using the windwing API specific code
    *
    * @param t_props the params required to create the window
    */
    virtual void createWindow(const windowProps& t_props) = 0;
    /**
    * @brief destroy the window using a windowing libary specific way
    */
    virtual void destroyWindow() = 0;

    /**
    * @brief set the size of the window
    *
    * @param t_size the size of the window
    */
    virtual void setWindowSize(const glm::vec2& t_size) = 0;
    /**
    * @brief set the position of the window
    *
    * @param t_pos the posotion of the window
    */
    virtual void setWindowPos(const glm::vec2& t_pos) = 0;
    /**
    * @brief set the title of the window
    *
    * @param t_title the window tile
    */
    virtual void setWindowTitle(const std::string& t_title) = 0;
    /**
    * @brief set the window swap interval
    *
    * @param t_fps the swap interval to set
    */
    virtual void setWindowSwapInterval(const int& t_fps) = 0;

    /**
    * @brief get the window size
    *
    * @return the size of the window
    */
    virtual glm::vec2 getWindowSize() const = 0;
    /**
    * @brief get the window position
    *
    * @return the position of the window
    */
    virtual glm::vec2 getWindowPos() const = 0;

    /**
    * @brief maximize the window
    */
    virtual void maximizeWindow() = 0;
    /**
    * @brief minimize the window
    */
    virtual void minimizeWindow() = 0;
    /**
    * @brief restore the window to original state 
    */
    virtual void restoreWindow() = 0;
    /**
    * @brief bring the window into focus
    */
    virtual void focusWindow() = 0;

    /* -- general util functions -- */
    // * TODO: set event function
    // void setEventFunction(eventCallbackFn t_fn);
    
    /**
    * @brief function called before renderng is done
    */
    virtual void preRender() = 0;
    /**
    * @brief function called after rendering is done
    */
    virtual void postRender() = 0;

    /**
    * @brief set the background color
    *
    * @param t_color the color (rgba) of the background
    */
    virtual void setBackgroundColor(const glm::vec4& t_color) = 0;

public:

    /**
    * @brief window props struct. all the information required to create a new window
    */
    struct windowProps {
        std::string m_title;
        int m_width;
        int m_height;
    };

    /**
    * @brief the driver data to store
    */
    struct driverData {
        glm::vec2 m_lastMousePos;
        bool m_firstMouseMove;
        // * TODO: add event callback to driver data
        // callbackFn m_eventFn = [](dm3Event&){};
    };

protected:

    // * TODO: store event fn
    // eventCallbackFn m_eventCallback;
    driverData m_driverData;
};

}

#endif

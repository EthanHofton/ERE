#ifndef ERE_API_WINDOW_API_HPP
#define ERE_API_WINDOW_API_HPP

#include <string>
#include <functional>
#include <memory>

namespace ere {

class windowAPI {
public:

    struct windowProps;
    // * TODO: create event handler
    // using eventCallbackFn = std::function<void util::event<>>;

    /**
    * @brief public access point for creating a window. each platform specitfic window will implament this API and implament the createWindow function
    * to return their version of a window
    *
    * @return a downcasted version of a concreate window impl
    */
    static std::shared_ptr<windowAPI> createConcreteWindow(const windowProps& t_props);

    /**
    * @brief windowAPI constructor. stores the props it gets
    *
    * @param t_props the window props needed to construct a window
    */
    windowAPI(const windowProps& t_props);

    /* -- pure virtual functions -- */
    virtual void createWindow(const windowProps& t_props) = 0;
    virtual void destroyWindow() = 0;

    virtual void setWindowSize() = 0;
    virtual void setWindowPos() = 0;
    virtual void setWindowTitle() = 0;
    virtual void setWindowSwapInterval() = 0;

    virtual void maximizeWindow() = 0;
    virtual void minimizeWindow() = 0;
    virtual void restoreWindow() = 0;
    virtual void focusWindow() = 0;

    /* -- general util functions -- */
    // * TODO: set event function
    // void setEventFunction(eventCallbackFn t_fn);

public:

    /**
    * @brief window props struct. all the information required to create a new window
    */
    struct windowProps {
        std::string m_title;
        int m_width;
        int m_height;
        int m_xpos;
        int m_ypos;
    };

protected:

    // * TODO: store event fn
    // eventCallbackFn m_eventCallback;
};

}

#endif

#ifndef __ERE_APPLICATION_HPP__
#define __ERE_APPLICATION_HPP__

#include "logger.hpp"
#include "core.hpp"

namespace ere {

class application {
public:

    /**
    * @brief create an application
    *
    * @return ref<application> the application
    */
    static ref<application> create_application();

    /**
    * @brief Construct a new application object
    */
    application();
    /**
    * @brief Destroy the application object
    */
    ~application();

};

}

#endif

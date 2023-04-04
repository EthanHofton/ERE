#ifndef __ERE_ENTRY_POINT_HPP__
#define __ERE_ENTRY_POINT_HPP__

#include "core.hpp"
#include "application.hpp"

namespace ere {

/**
* @brief create an application. To be implemented by the client.
*
* @return ref<application> the application
*/
extern ref<application> ere_create_application();

}

#endif

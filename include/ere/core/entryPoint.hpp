#ifndef ERE_CORE_ENTRY_POINT_HPP
#define ERE_CORE_ENTRY_POINT_HPP

#include "application.hpp"
#include <memory>

namespace ere {

/**
* @brief external create application function to be defined by user
*
* @return ere::application a fully initalized ere::application
*/
extern ref<ere::application> createApplication();

}

#endif

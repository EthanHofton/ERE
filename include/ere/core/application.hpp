#ifndef __ERE_APPLICATION_HPP__
#define __ERE_APPLICATION_HPP__

#include "logger.hpp"

namespace ere {

class application {
public:

    application() { ERE_INFO("Application created"); }
    ~application() { ERE_INFO("Application destroyed"); }
};

}

#endif

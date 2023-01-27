#ifndef ERE_CORE_APPLICATION_HPP
#define ERE_CORE_APPLICATION_HPP

#include <util/timer.hpp>

namespace ere {

class application {
public:

    application();
    ~application();

    void run();
    void onEvent();

private:

    util::manual_timer m_timer;

};

}

#endif

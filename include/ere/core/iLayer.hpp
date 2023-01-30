#ifndef ERE_CORE_I_LAYER_HPP
#define ERE_CORE_I_LAYER_HPP

#include <ere/events/events.hpp>

namespace ere {

class iLayer {
public:
    virtual ~iLayer() = default;
    virtual void onEvent(ereEvent& t_event) = 0;
};

}

#endif

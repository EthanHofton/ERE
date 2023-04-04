#ifndef __ERE_I_LAYER_HPP__
#define __ERE_I_LAYER_HPP__

#include <ere/events/events.hpp>

namespace ere {

class i_layer {
public:
    /**
    * @brief Destruct a new i_layer object
    */
    virtual ~i_layer() = default;
    /**
    * @brief run on every event
    *
    * @param t_event event to handle
    */
    virtual void on_event(ere_event& t_event) = 0;
};

}

#endif

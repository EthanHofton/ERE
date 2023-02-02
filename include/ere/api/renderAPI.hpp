#ifndef ERE_API_RENDER_API_HPP
#define ERE_API_RENDER_API_HPP

#include "bufferAPI.hpp"
#include "vertexArrayAPI.hpp"

namespace ere {

class renderAPI {
public:

    virtual ~renderAPI() = default;

    virtual void init() = 0;
    virtual void drawIndexed(const ref<vertexArrayAPI>& t_vertexArray, uint32_t t_indexCount = 0) = 0;
    static scope<renderAPI> make();
};

}


#endif

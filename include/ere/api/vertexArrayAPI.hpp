#ifndef ERE_API_VEREX_ARRAY_API_HPP
#define ERE_API_VEREX_ARRAY_API_HPP

#include "bufferAPI.hpp"

namespace ere {

class vertexArrayAPI {
public:
    virtual ~vertexArrayAPI() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(const ref<vertexBufferAPI>& t_vertexBuffer) = 0;
    virtual void addIndexBuffer(const ref<indexBufferAPI>& t_indexBuffer) = 0;

    virtual const std::vector<ref<vertexBufferAPI>>& getVertexBuffers() const = 0;
    virtual const ref<indexBufferAPI>& getIndexBuffer() const = 0;

    static ref<vertexArrayAPI> make();
};

}

#endif

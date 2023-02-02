#ifndef ERE_API_VEREX_ARRAY_API_HPP
#define ERE_API_VEREX_ARRAY_API_HPP

#include "bufferAPI.hpp"

namespace ere {

class vertexArray {
public:
    virtual ~vertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(const vertexBuffer& t_vertexBuffer) = 0;
    virtual void addIndexBuffer(const indexBuffer& t_indexBuffer) = 0;

    virtual const std::vector<vertexBuffer&> getVertexBuffers() const = 0;
    virtual const indexBuffer& getIndexBuffer() const = 0;

    static vertexArray& make();
};

}

#endif

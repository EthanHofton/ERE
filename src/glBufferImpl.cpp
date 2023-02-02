#include <ere/impl/opengl/glBufferImpl.hpp>

#ifdef USE_OPENGL

namespace ere {

/* -- VERTEX BUFFER -- */

ref<vertexBufferAPI> vertexBufferAPI::make(const uint32_t &t_size) {
    return createRef<glVertexBuffer>(t_size);
}

ref<vertexBufferAPI> vertexBufferAPI::make(void *t_vertices, const uint32_t &t_size) {
    return createRef<glVertexBuffer>(t_vertices, t_size);
}

/* -- INDEX BUFFER -- */

ref<indexBufferAPI> indexBufferAPI::make(const uint32_t &t_size) {
    return createRef<glIndexBuffer>(t_size);
}

ref<indexBufferAPI> indexBufferAPI::make(uint32_t *t_indices, const uint32_t &t_size) {
    return createRef<glIndexBuffer>(t_indices, t_size);
}

}

#endif

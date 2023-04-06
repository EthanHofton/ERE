#ifndef __ERE_VERTEX_ARRAY_API_HPP__
#define __ERE_VERTEX_ARRAY_API_HPP__

#include "vertex_buffer_api.hpp"
#include "index_buffer_api.hpp"

namespace ere {

class vertex_array_api {
public:

    virtual ~vertex_array_api() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void add_vertex_buffer(const ref<vertex_buffer_api>& t_vbo) = 0;
    virtual void set_index_buffer(const ref<index_buffer_api>& t_ibo) = 0;

    inline const std::vector<ref<vertex_buffer_api>>& get_vertex_buffers() const { return m_vbos; } 
    inline const ref<index_buffer_api>& get_index_buffer() const { return m_ibo; }

    static ref<vertex_array_api> create_vertex_array_api();

private:

    std::vector<ref<vertex_buffer_api>> m_vbos;
    ref<index_buffer_api> m_ibo = nullptr;
};

}

#endif // __ERE_VERTEX_ARRAY_API_HPP__

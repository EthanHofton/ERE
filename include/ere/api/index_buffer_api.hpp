#ifndef __ERE_INDEX_BUFFER_API_HPP__
#define __ERE_INDEX_BUFFER_API_HPP__

#include <stdint.h>
#include <ere/core/core.hpp>

namespace ere {

class index_buffer_api {
public:

    virtual ~index_buffer_api() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    inline uint32_t get_count() const { return m_count; }

    static ref<index_buffer_api> create_index_buffer_api(uint32_t t_size);
    static ref<index_buffer_api> create_index_buffer_api(uint32_t* t_data, uint32_t t_size);

private:

    uint32_t m_count = 0;
};

}

#endif // __ERE_INDEX_BUFFER_API_HPP__

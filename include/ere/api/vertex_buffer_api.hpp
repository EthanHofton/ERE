#ifndef __ERE_VERTEX_BUFFER_API_HPP__
#define __ERE_VERTEX_BUFFER_API_HPP__

#include <stdint.h>
#include <string>
#include <vector>
#include <ere/core/core.hpp>

namespace ere {

class buffer_layout {

    struct buffer_element {
        std::string name;
        uint32_t size;
        uint32_t count;
        bool normalized;
    };
    using iterator = std::vector<buffer_element>::iterator;
    using const_iterator = std::vector<buffer_element>::const_iterator;

    buffer_layout() = default;
    inline buffer_layout(std::initializer_list<buffer_element> t_elements) : m_elements(t_elements) {}

    inline uint32_t get_stride() const { return m_stride; }
    inline const std::vector<buffer_element>& get_elements() const { return m_elements; }

    inline iterator begin() { return m_elements.begin(); }
    inline const_iterator begin() const { return m_elements.begin(); }
    inline const_iterator cbegin() const { return m_elements.cbegin(); }

    inline iterator end() { return m_elements.end(); }
    inline const_iterator end() const { return m_elements.end(); }
    inline const_iterator cend() const { return m_elements.end(); }

private:

    std::vector<buffer_element> m_elements;
    uint32_t m_stride = 0;

};

class vertex_buffer_api {
public:

    virtual ~vertex_buffer_api() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void set_data(const void* t_data, uint32_t t_size) = 0;

    inline void set_layout(const buffer_layout& t_layout) { m_layout = t_layout; }
    inline const buffer_layout& get_layout() const { return m_layout; }

    static ref<vertex_buffer_api> create_vertex_buffer_api(uint32_t t_size);
    static ref<vertex_buffer_api> create_vertex_buffer_api(const void* t_data, uint32_t t_size);

private:

    void* m_data;
    uint32_t m_size;
    buffer_layout m_layout;
};

}

#endif

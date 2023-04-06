#ifndef __ERE_VERTEX_BUFFER_API_HPP__
#define __ERE_VERTEX_BUFFER_API_HPP__

#include <stdint.h>
#include <string>
#include <vector>
#include <ere/core/core.hpp>

namespace ere {

class buffer_layout {
public:

    enum class shader_type {
        float_1,
        float_2,
        float_3,
        float_4,
        int_1,
        int_2,
        int_3,
        int_4,
        bool_1,
        matf_3,
        matf_4,
    };

    struct buffer_element {

        std::string name;
        uint32_t size;
        uint32_t count;
        size_t offset;
        bool normalized;
        shader_type type;
    };
    using iterator = std::vector<buffer_element>::iterator;
    using const_iterator = std::vector<buffer_element>::const_iterator;

    buffer_layout() = default;
    inline buffer_layout(std::initializer_list<buffer_element> t_elements) : m_elements(t_elements) {
        size_t offset = 0;
        for (auto& element : m_elements) {
            element.offset = offset;
            offset += element.size;
            m_stride += element.size;
        }
    }

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

    inline uint32_t get_data_size() const { return m_data_size; }
    inline uint32_t get_buffer_size() const { return m_buffer_size; }

    static ref<vertex_buffer_api> create_vertex_buffer_api(uint32_t t_size);
    static ref<vertex_buffer_api> create_vertex_buffer_api(const void* t_data, uint32_t t_size);

private:

    void* m_data;
    uint32_t m_data_size;
    uint32_t m_buffer_size;
    buffer_layout m_layout;
};

}

#endif

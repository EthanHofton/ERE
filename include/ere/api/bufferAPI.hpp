#ifndef ERE_API_BUFFER_API_HPP
#define ERE_API_BUFFER_API_HPP

#include <stdint.h>
#include <string>
#include <vector>

namespace ere {

enum class shaderDataType {
    Bool, Int, UInt, Float, Double, /* -- SCALARS -- */
    BVec2, BVec3, BVec4,            /* -- BOOL VECTORS -- */
    IVec2, IVec3, IVec4,            /* -- INT VECTORS -- */
    UVec2, UVec3, UVec4,            /* -- UINT VECTORS -- */
    Vec2, Vec3, Vec4,               /* -- FLOAT VECTORS -- */
    DVec2, DVec3, DVec4             /* -- DOUBLE VECTORS -- */
};

static uint32_t shaderDataTypeSize(const shaderDataType& t_type) {
    switch (t_type) {
        case shaderDataType::Bool:   return 1;
        case shaderDataType::Int:    return 4;
        case shaderDataType::UInt:   return 4;
        case shaderDataType::Float:  return 4;
        case shaderDataType::Double: return 8;
        case shaderDataType::BVec2:  return shaderDataTypeSize(shaderDataType::Bool)   * 2;
        case shaderDataType::BVec3:  return shaderDataTypeSize(shaderDataType::Bool)   * 3;
        case shaderDataType::BVec4:  return shaderDataTypeSize(shaderDataType::Bool)   * 4;
        case shaderDataType::IVec2:  return shaderDataTypeSize(shaderDataType::Int)    * 2;
        case shaderDataType::IVec3:  return shaderDataTypeSize(shaderDataType::Int)    * 3;
        case shaderDataType::IVec4:  return shaderDataTypeSize(shaderDataType::Int)    * 4;
        case shaderDataType::UVec2:  return shaderDataTypeSize(shaderDataType::UInt)   * 2;
        case shaderDataType::UVec3:  return shaderDataTypeSize(shaderDataType::UInt)   * 3;
        case shaderDataType::UVec4:  return shaderDataTypeSize(shaderDataType::UInt)   * 4;
        case shaderDataType::Vec2:   return shaderDataTypeSize(shaderDataType::Float)  * 2;
        case shaderDataType::Vec3:   return shaderDataTypeSize(shaderDataType::Float)  * 3;
        case shaderDataType::Vec4:   return shaderDataTypeSize(shaderDataType::Float)  * 4;
        case shaderDataType::DVec2:  return shaderDataTypeSize(shaderDataType::Double) * 2;
        case shaderDataType::DVec3:  return shaderDataTypeSize(shaderDataType::Double) * 3;
        case shaderDataType::DVec4:  return shaderDataTypeSize(shaderDataType::Double) * 4;
    }

    return 0;
}

class bufferLayout {
public:

    struct bufferElement {
        std::string m_name;
        shaderDataType m_type;
        uint32_t m_size;
        size_t m_offset;
        bool m_normalized;

        bufferElement() = default; 

        uint32_t getComponentCount() const {
            switch (m_type) {
                case shaderDataType::Bool:   return 1;
                case shaderDataType::Int:    return 1;
                case shaderDataType::UInt:   return 1;
                case shaderDataType::Float:  return 1;
                case shaderDataType::Double: return 1;
                case shaderDataType::BVec2:  return 2;
                case shaderDataType::BVec3:  return 3;
                case shaderDataType::BVec4:  return 4;
                case shaderDataType::IVec2:  return 2;
                case shaderDataType::IVec3:  return 3;
                case shaderDataType::IVec4:  return 4;
                case shaderDataType::UVec2:  return 2;
                case shaderDataType::UVec3:  return 3;
                case shaderDataType::UVec4:  return 4;
                case shaderDataType::Vec2:   return 2;
                case shaderDataType::Vec3:   return 3;
                case shaderDataType::Vec4:   return 4;
                case shaderDataType::DVec2:  return 2;
                case shaderDataType::DVec3:  return 3;
                case shaderDataType::DVec4:  return 4;
            }

            return 0;
        }
    };
    using iterator = std::vector<bufferElement>::iterator;
    using const_iterator = std::vector<bufferElement>::const_iterator;

    bufferLayout() {}
    bufferLayout(std::initializer_list<bufferElement> t_elem) : m_elements(t_elem) {}

    uint32_t getStride() { return m_stride; }
    const std::vector<bufferElement>& getElements() const { return m_elements; }

    iterator begin() { return m_elements.begin(); } 
    const_iterator begin() const { return m_elements.begin(); }
    const_iterator cbegin() const { return m_elements.cbegin(); }

    iterator end() { return m_elements.end(); } 
    const_iterator end() const { return m_elements.end(); }
    const_iterator cend() const { return m_elements.cend(); }

private:

    std::vector<bufferElement> m_elements;
    uint32_t m_stride = 0;
};

class vertexBuffer {
public:

    virtual ~vertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setData(const void* t_data, uint32_t t_size) = 0;
    virtual const bufferLayout& getLayout() const = 0;
    virtual void setLayout(const bufferLayout& t_layout) = 0;

    static vertexBuffer& make(const uint32_t& t_size);
    static vertexBuffer& make(void* t_vertices, const uint32_t& t_size);

private:

    void* m_data;
    uint32_t m_dataSize;
    bufferLayout m_layout;
};

class indexBuffer {
public:
    virtual ~indexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setData(uint32_t* t_indices, uint32_t t_size) = 0;

    static indexBuffer& make(const uint32_t& t_size);
    static indexBuffer& make(uint32_t* t_indices, const uint32_t& t_size);
};

}

#endif

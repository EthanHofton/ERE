#ifndef __ERE_OPENGL_VERTEX_ARRAY_HPP__
#define __ERE_OPENGL_VERTEX_ARRAY_HPP__

#include <ere/ere_config.hpp>
#ifdef USE_OPENGL
#include <glad/glad.h>

#include <ere/api/vertex_array_api.hpp>


namespace ere {

static GLenum ere_shader_type_to_gl(const buffer_layout::shader_type& t_type);

class opengl_vertex_array : public vertex_array_api {
public:

    opengl_vertex_array();
    virtual ~opengl_vertex_array();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void add_vertex_buffer(const ref<vertex_buffer_api>& t_vbo) override;
    virtual void set_index_buffer(const ref<index_buffer_api>& t_ibo) override;

private:

    unsigned int m_VAO;
    int m_index = 0;

};

}

#endif // USE_OPENGL

#endif // __ERE_OPENGL_VERTEX_ARRAY_HPP__

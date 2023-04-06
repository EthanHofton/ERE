#ifndef __ERE_OPENGL_SHADER_HPP__
#define __ERE_OPENGL_SHADER_HPP__

#include <ere/ere_config.hpp>

#ifdef USE_OPENGL

#include <ere/api/shader_api.hpp>
#include <map>

namespace ere {

class opengl_shader : public shader_api {
public:

    opengl_shader(const std::string& t_vertex_src, const std::string& t_fragment_src);
    opengl_shader(const std::string& t_vertex_src, const std::string& t_geometry_src, const std::string& t_fragment_src);
    virtual ~opengl_shader();

    virtual void bind() const override;
    virtual void unbind() const override;

    virtual void set_uniform_1i(const std::string& t_name, int t_value) override;
    virtual void set_uniform_1f(const std::string& t_name, float t_value) override;
    virtual void set_uniform_2f(const std::string& t_name, const glm::vec2& t_value) override;
    virtual void set_uniform_3f(const std::string& t_name, const glm::vec3& t_value) override;
    virtual void set_uniform_4f(const std::string& t_name, const glm::vec4& t_value) override;
    virtual void set_uniform_mat4f(const std::string& t_name, const glm::mat4& t_value) override;

private:

    void link_shader(std::initializer_list<unsigned int> t_shader_ids);
    unsigned int compile_shader(const std::string& t_src, unsigned int t_type);

    unsigned int m_shader_id;

};

}

#endif // USE_OPENGL

#endif // __ERE_OPENGL_SHADER_HPP__

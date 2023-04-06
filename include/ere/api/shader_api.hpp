#ifndef __ERE_SHADER_API_HPP__
#define __ERE_SHADER_API_HPP__

#include <ere/core/core.hpp>
#include <ere/core/logger.hpp>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <string>

namespace ere {

class shader_api {
public:

    virtual ~shader_api() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void set_uniform_1i(const std::string& t_name, int t_value) = 0;
    virtual void set_uniform_1f(const std::string& t_name, float t_value) = 0;
    virtual void set_uniform_2f(const std::string& t_name, const glm::vec2& t_value) = 0;
    virtual void set_uniform_3f(const std::string& t_name, const glm::vec3& t_value) = 0;
    virtual void set_uniform_4f(const std::string& t_name, const glm::vec4& t_value) = 0;
    virtual void set_uniform_mat4f(const std::string& t_name, const glm::mat4& t_value) = 0;

    static ref<shader_api> create_shader_api(const std::string& t_vertex_src, const std::string& t_fragment_src);
    static ref<shader_api> create_shader_api(const std::string& t_vertex_src, const std::string& t_geometry_src, const std::string& t_fragment_src);

    inline static ref<shader_api> create_shader_api_from_file(const std::string& t_vertex_src, const std::string& t_fragment_src) {
        return create_shader_api(load_file(t_vertex_src), load_file(t_fragment_src));
    }
    inline static ref<shader_api> create_shader_api_from_file(const std::string& t_vertex_src, const std::string& t_geometry_src, const std::string& t_fragment_src) {
        return create_shader_api(load_file(t_vertex_src), load_file(t_geometry_src), load_file(t_fragment_src));
    }

private:

    static std::string load_file(const std::string& t_filepath) {
        // read a file into a string
        std::ifstream file_stream(t_filepath);
        if (!file_stream.is_open()) {
            ERE_ERROR("Failed to open file: {}", t_filepath);
            return "";
        }

        std::ostringstream buffer;
        buffer << file_stream.rdbuf();
        return buffer.str();
    }

};

}

#endif // __ERE_SHADER_API_HPP__

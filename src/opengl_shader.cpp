#include <ere/impl/opengl/opengl_shader.hpp>

#ifdef USE_OPENGL

#include <glad/glad.h>

namespace ere {

ref<shader_api> shader_api::create_shader_api(const std::string& t_vertex_src, const std::string& t_fragment_src)
{
    return std::make_shared<opengl_shader>(t_vertex_src, t_fragment_src);
}

ref<shader_api> shader_api::create_shader_api(const std::string &t_vertex_src, const std::string &t_geometry_src, const std::string &t_fragment_src) {
    return std::make_shared<opengl_shader>(t_vertex_src, t_geometry_src, t_fragment_src);
}

opengl_shader::opengl_shader(const std::string& t_vertex_src, const std::string& t_fragment_src) {
    // create shader program
    m_shader_id = glCreateProgram();

    // compile shaders
    unsigned int vertex_shader_id = compile_shader(t_vertex_src, GL_VERTEX_SHADER);
    unsigned int fragment_shader_id = compile_shader(t_fragment_src, GL_FRAGMENT_SHADER);

    // link shaders
    link_shader({ vertex_shader_id, fragment_shader_id });

    ERE_INFO("shader program created");
}

opengl_shader::opengl_shader(const std::string& t_vertex_src, const std::string& t_geometry_src, const std::string& t_fragment_src) {
    // create shader program
    m_shader_id = glCreateProgram();

    // compile shaders
    unsigned int vertex_shader_id = compile_shader(t_vertex_src, GL_VERTEX_SHADER);
    unsigned int fragment_shader_id = compile_shader(t_fragment_src, GL_FRAGMENT_SHADER);
    unsigned int geometry_shader_id = compile_shader(t_geometry_src, GL_GEOMETRY_SHADER);

    // link shaders
    link_shader({ vertex_shader_id, fragment_shader_id, geometry_shader_id });

    ERE_INFO("shader program created");
}

unsigned int opengl_shader::compile_shader(const std::string& t_src, unsigned int t_type) {
    unsigned int shader_id = glCreateShader(t_type);

    std::string shader_type = t_type == GL_VERTEX_SHADER ? "vertex" : ((t_type == GL_FRAGMENT_SHADER) ? "fragment" : "geometry");
    ERE_INFO("Compiling {} shader", shader_type);

    const char* src = t_src.c_str();
    glShaderSource(shader_id, 1, &src, nullptr);
    glCompileShader(shader_id);

    // check for shader errors
    int success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader_id, 512, nullptr, info_log);
        ERE_ERROR("Failed to compile {} shader: {}", shader_type, info_log);
    }

    return shader_id;
}

void opengl_shader::link_shader(std::initializer_list<unsigned int> t_shader_ids) {
    for (auto shader_id : t_shader_ids) {
        glAttachShader(m_shader_id, shader_id);
    }
    ERE_INFO("Linking shader program");
    glLinkProgram(m_shader_id);

    // check for program linking errors
    int success;
    glGetProgramiv(m_shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(m_shader_id, 512, nullptr, info_log);
        ERE_ERROR("Failed to link shader program: {}", info_log);
    }

    // delete shaders
    for (auto shader_id : t_shader_ids) {
        glDeleteShader(shader_id);
    }
}

opengl_shader::~opengl_shader() {
    glDeleteProgram(m_shader_id);
}

void opengl_shader::bind() const {
    glUseProgram(m_shader_id);

    for (auto& [name, value] : m_uniform_1f_cache) {
        glUniform1f(glGetUniformLocation(m_shader_id, name.c_str()), value);
    }
    for (auto& [name, value] : m_uniform_2f_cache) {
        glUniform2f(glGetUniformLocation(m_shader_id, name.c_str()), value.x, value.y);
    }
    for (auto& [name, value] : m_uniform_3f_cache) {
        glUniform3f(glGetUniformLocation(m_shader_id, name.c_str()), value.x, value.y, value.z);
    }
    for (auto& [name, value] : m_uniform_4f_cache) {
        glUniform4f(glGetUniformLocation(m_shader_id, name.c_str()), value.x, value.y, value.z, value.w);
    }
    for (auto& [name, value] : m_uniform_1i_cache) {
        glUniform1i(glGetUniformLocation(m_shader_id, name.c_str()), value);
    }
    for (auto& [name, value] : m_uniform_mat4f_cache) {
        glUniformMatrix4fv(glGetUniformLocation(m_shader_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }
}

void opengl_shader::unbind() const {
    glUseProgram(0);
}

void opengl_shader::set_uniform_1i(const std::string& t_name, int t_value) {
    m_uniform_1f_cache[t_name] = t_value;
}

void opengl_shader::set_uniform_1f(const std::string& t_name, float t_value) {
    m_uniform_1f_cache[t_name] = t_value;
}

void opengl_shader::set_uniform_2f(const std::string& t_name, const glm::vec2& t_value) {
    m_uniform_2f_cache[t_name] = t_value;
}

void opengl_shader::set_uniform_3f(const std::string& t_name, const glm::vec3& t_value) {
    m_uniform_3f_cache[t_name] = t_value;
}

void opengl_shader::set_uniform_4f(const std::string& t_name, const glm::vec4& t_value) {
    m_uniform_4f_cache[t_name] = t_value;
}

void opengl_shader::set_uniform_mat4f(const std::string& t_name, const glm::mat4& t_value) {
    m_uniform_mat4f_cache[t_name] = t_value;
}

}

#endif

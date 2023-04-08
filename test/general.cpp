#include <ere/core/entry_point.hpp>
#include <ere/core/layer.hpp>
#include <ere/mappings/key_map.hpp>
#include <ere/api/render_api.hpp>
#include <ere/api/texture_api.hpp>
#include <ere/core/camera_3d.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

namespace ere {

struct mesh {
public:

    mesh(const std::vector<glm::vec3>& t_vertices, const std::vector<glm::vec2>& t_uv, const std::vector<glm::vec3>& t_normals, const std::vector<unsigned int>& t_indices, ref<shader_api>& t_shader) {
        m_shader = t_shader;

        // create the vao
        m_vao = vertex_array_api::create_vertex_array_api();

        m_vertices = t_vertices;
        m_uv = t_uv;
        m_normals = t_normals;
        m_indices = t_indices;

        // create the vbos
        m_vbo_vetices = vertex_buffer_api::create_vertex_buffer_api(m_vertices.data(), m_vertices.size() * sizeof(glm::vec3));
        m_vbo_uv = vertex_buffer_api::create_vertex_buffer_api(m_uv.data(), m_uv.size() * sizeof(glm::vec2));
        m_vbo_normals = vertex_buffer_api::create_vertex_buffer_api(m_uv.data(), m_uv.size() * sizeof(glm::vec3));

        // create the ibo
        m_ibo = index_buffer_api::create_index_buffer_api(m_indices.data(), m_indices.size() * sizeof(uint32_t));

        buffer_layout layout_vertices = {
            { "aPosition", buffer_layout::shader_type::float_3, false },
        };

        buffer_layout layout_uv = {
            { "aUv", buffer_layout::shader_type::float_2, false },
        };

        buffer_layout layout_normals = {
            { "aNormal", buffer_layout::shader_type::float_3, false },
        };

        m_vbo_vetices->set_layout(layout_vertices);
        m_vbo_uv->set_layout(layout_uv);
        m_vbo_normals->set_layout(layout_normals);

        // add the vbos to the vao
        m_vao->add_vertex_buffer(m_vbo_vetices);
        m_vao->add_vertex_buffer(m_vbo_uv);
        m_vao->add_vertex_buffer(m_vbo_normals);

        // add the ibo to the vao
        m_vao->set_index_buffer(m_ibo);
    }

    void draw() {
        render_api::draw_indexed_textured(m_vao, m_shader, m_textures);
    }

    void set_texture(const std::vector<ref<texture_api>>& t_textures) { m_textures = t_textures; }
    void add_texture(const ref<texture_api>& t_texture) { m_textures.push_back(t_texture); }
    void add_textures(const std::vector<ref<texture_api>>& t_textures) { m_textures.insert(m_textures.end(), t_textures.begin(), t_textures.end()); }

private:

    ref<vertex_array_api> m_vao;

    ref<vertex_buffer_api> m_vbo_vetices;
    ref<vertex_buffer_api> m_vbo_uv;
    ref<vertex_buffer_api> m_vbo_normals;

    ref<index_buffer_api> m_ibo;
    
    ref<shader_api> m_shader;

    std::vector<ref<texture_api>> m_textures;

    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_uv;
    std::vector<glm::vec3> m_normals;
    std::vector<uint32_t> m_indices;
};

struct texture {
    std::string path;
    ref<texture_api> texture;
};

class model {
public:
    
    model(const std::string& t_path) {
        m_shader = shader_api::create_shader_api_from_file("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
        load_model(t_path);
    }

    void draw() {
        for (auto& mesh : m_meshes) {
            mesh.draw();
        }
    }

private:

    // load model using assimp
    void load_model(const std::string& t_path) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(t_path, aiProcess_Triangulate | aiProcess_FlipUVs);
        // const aiScene *scene = importer.ReadFile(t_path, aiProcess_Triangulate);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            ERE_INFO("ERROR::ASSIMP::{}", importer.GetErrorString());
            return;
        }

        m_directory = t_path.substr(0, t_path.find_last_of('/'));

        process_node(scene->mRootNode, scene);
    }

    void process_node(aiNode* t_node, const aiScene* t_scene) {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < t_node->mNumMeshes; i++) {
            aiMesh* mesh = t_scene->mMeshes[t_node->mMeshes[i]];
            m_meshes.push_back(process_mesh(mesh, t_scene));
        }

        // then do the same for each of its children
        for (unsigned int i = 0; i < t_node->mNumChildren; i++) {
            process_node(t_node->mChildren[i], t_scene);
        }
    }

    mesh process_mesh(aiMesh* t_mesh, const aiScene *t_secne) {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < t_mesh->mNumVertices; i++) {
            glm::vec3 vertex;
            vertex.x = t_mesh->mVertices[i].x;
            vertex.y = t_mesh->mVertices[i].y;
            vertex.z = t_mesh->mVertices[i].z;
            vertices.push_back(vertex);

            glm::vec2 uv_coords;
            if (t_mesh->mTextureCoords[0]) {
                uv_coords.x = t_mesh->mTextureCoords[0][i].x;
                uv_coords.y = t_mesh->mTextureCoords[0][i].y;
            } else {
                uv_coords.x = 0.0f;
                uv_coords.y = 0.0f;
            }
            uv.push_back(uv_coords);

            glm::vec3 normal;
            if (t_mesh->HasNormals()) {
                normal.x = t_mesh->mNormals[i].x;
                normal.y = t_mesh->mNormals[i].y;
                normal.z = t_mesh->mNormals[i].z;
            } else {
                normal.x = 0.0f;
                normal.y = 0.0f;
                normal.z = 0.0f;
            }
            normals.push_back(normal);
        }

        for (unsigned int i = 0; i < t_mesh->mNumFaces; i++) {
            aiFace face = t_mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        mesh m(vertices, uv, normals, indices, m_shader);

        if (t_mesh->mMaterialIndex >= 0) {
            aiMaterial* material = t_secne->mMaterials[t_mesh->mMaterialIndex];
            std::vector<ref<texture_api>> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            m.add_textures(diffuse_maps);
            std::vector<ref<texture_api>> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
            m.add_textures(specular_maps);
            std::vector<ref<texture_api>> normal_maps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
            m.add_textures(normal_maps);
        }

        return m;
    }

    std::vector<ref<texture_api>> load_material_textures(aiMaterial* t_mat, aiTextureType t_type, const std::string& t_type_name) {
        std::vector<ref<texture_api>> textures;
        if (t_mat->GetTextureCount(t_type) > 1) {
            ERE_INFO("WARNING::MODEL::TEXTURE::{}::{}", t_type_name, "more than one texture of the same type");
        }
        for (unsigned int i = 0; i < t_mat->GetTextureCount(t_type); i++) {
            aiString str;
            t_mat->GetTexture(t_type, i, &str);
            bool skip = false;
            for (unsigned int j = 0; j < m_textures_loaded.size(); j++) {
                if (std::strcmp(m_textures_loaded[j].path.c_str(), str.C_Str()) == 0) {
                    textures.push_back(m_textures_loaded[j].texture);
                    skip = true;
                    break;
                }
            }

            if (!skip) {
                ref<texture_api> texture = texture_api::create_texture_api(m_directory + "/" + str.C_Str());
                texture->set_uniform_name(t_type_name);
                textures.push_back(texture);
                m_textures_loaded.push_back({str.C_Str(), texture});
            }
        }

        return textures;
    }

private:

    std::vector<mesh> m_meshes;
    std::string m_directory;
    std::vector<texture> m_textures_loaded;
    ref<shader_api> m_shader;
};

class model_layer : public layer {
public:

    bool on_mouse_moved(mouse_moved_event& e) override {
        m_camera->on_mouse_moved(e);
        return true;
    }

    bool on_mouse_scrolled(mouse_scrolled_event& e) override {
        m_camera->on_mouse_scrolled(e);
        return true;
    }

    bool on_key_pressed(key_pressed_event& e) override {
        m_camera->on_key_pressed(e);
        return true;
    }

    bool on_update(update_event& e) override {
        m_camera->on_update(e);

        m_model->draw();

        return true;
    }

    bool on_attach(attach_event& e) override {
        m_camera = createRef<camera_3d>(application::get_application()->get_window_size().x / application::get_application()->get_window_size().y);
        m_camera->set_far(10000.f);
        // m_camera->set_move_speed(250);
        render_api::get_renderer()->set_camera(m_camera);
    
        m_model = createRef<model>("assets/backpack/backpack.obj");
        // m_model = createRef<model>("assets/Sponza/sponza.obj");

        return true;
    }

    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowMetricsWindow();
        return true;
    }

private:

    ref<camera_3d> m_camera;
    ref<model> m_model;
};

class l1 : public layer {
public:

    bool on_key_pressed(key_pressed_event& e) override {
        if (e.get_key_code() == ERE_KEY_C) {
            application::get_application()->set_background_color({0.1f, 1.f, 0.1f, 1.0f});
        }
    
        m_camera->on_key_pressed(e);

        return true;
    }

    bool on_mouse_moved(mouse_moved_event& e) override {
        m_camera->on_mouse_moved(e);
        return true;
    }

    bool on_mouse_scrolled(mouse_scrolled_event& e) override {
        m_camera->on_mouse_scrolled(e);
        return true;
    }

    bool on_attach(attach_event& e) override {
        // create the camera
        m_camera = createRef<camera_3d>(application::get_application()->get_window_size().x / application::get_application()->get_window_size().y);
        render_api::set_camera(m_camera);

        // create the texture
        m_container_texture = texture_api::create_texture_api("assets/images/container.jpg");
        m_container_texture->set_uniform_name("uContainer");

        // create the shader
        m_shader = shader_api::create_shader_api_from_file("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

        // create the triangle data
        m_square_pos = {
           -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f,  0.5f, 0.f,
           -0.5f,  0.5f, 0.f
        };

        m_square_colors = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f
        };

        m_square_uv = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        };

        m_square_indices = {
            0, 1, 2,
            2, 3, 0
        };

        // create the vertex array
        m_vao = vertex_array_api::create_vertex_array_api();

        // create the vertex buffer
        m_vbo_pos = vertex_buffer_api::create_vertex_buffer_api(m_square_pos.data(), m_square_pos.size() * sizeof(float));

        // create the vertex buffer layout
        buffer_layout layout = {
            { "aPos", buffer_layout::shader_type::float_3, false }
        };

        // set the layout
        m_vbo_pos->set_layout(layout);
        m_vao->add_vertex_buffer(m_vbo_pos);

        m_vbo_color = vertex_buffer_api::create_vertex_buffer_api(m_square_colors.data(), m_square_colors.size() * sizeof(float));

        // create the vertex buffer layout
        buffer_layout layout2 = {
            { "aColor", buffer_layout::shader_type::float_3, false }
        };

        // set the layout
        m_vbo_color->set_layout(layout2);

        // add the vertex buffer to the vertex array
        m_vao->add_vertex_buffer(m_vbo_color);

        m_vbo_uv = vertex_buffer_api::create_vertex_buffer_api(m_square_uv.data(), m_square_uv.size() * sizeof(float));

        // create the vertex buffer layout
        buffer_layout layout3 = {
            { "aUv", buffer_layout::shader_type::float_2, false }
        };

        // set the layout
        m_vbo_uv->set_layout(layout3);

        // add the vertex buffer to the vertex array
        m_vao->add_vertex_buffer(m_vbo_uv);

        // create the index buffer
        m_ibo = index_buffer_api::create_index_buffer_api(m_square_indices.data(), m_square_indices.size() * sizeof(uint32_t));
        m_vao->set_index_buffer(m_ibo);

        return false;
    }

    bool on_update(update_event& e) override {
        m_camera->on_update(e);

        render_api::draw_indexed_textured(m_vao, m_shader, {m_container_texture});

        return false;
    }

    bool on_imgui_update(imgui_update_event& e) override {
        ImGui::ShowDemoWindow();
        return false;
    }

private:

    ref<shader_api> m_shader;

    ref<texture_api> m_container_texture;

    ref<vertex_array_api> m_vao;
    ref<vertex_buffer_api> m_vbo_pos;
    ref<vertex_buffer_api> m_vbo_color;
    ref<vertex_buffer_api> m_vbo_uv;

    ref<index_buffer_api> m_ibo;

    std::vector<float> m_square_pos;
    std::vector<float> m_square_colors;
    std::vector<float> m_square_uv;
    std::vector<uint32_t> m_square_indices;

    ref<camera_3d> m_camera;

    util::raii_timer m_timer;
};

ref<ere::application> ere_create_application() {
    ref<application> app = application::get_application();

    app->push_layer(createRef<model_layer>());

    app->set_background_color({.529f, .808f, .922f, 1.0f});
    app->set_fps(120.0);
    app->set_window_title("Ere Engine TEST CHANGE");
    app->vsync(false);
    app->set_relative_mouse_mode(true);

    return app;
}

}

#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include "mesh.hpp"
#include "light_scene.hpp"
#include "light.hpp"
#include <ere/core/core.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ere {

struct texture {
    std::string path;
    ref<texture2d_api> texture;
};

class model {
public:
    
    model(const std::string& t_path, ref<light_scene> t_light_scene) {
        m_light_scene = t_light_scene;
        load_model(t_path);
    }

    void draw() {
        for (auto& mesh : m_meshes) {
            auto shader = m_light_scene->get_shader(mesh.get_material());
            mesh.draw(shader);
        }
    }

private:

    // load model using assimp
    void load_model(const std::string& t_path) {
        Assimp::Importer importer;
        // const aiScene *scene = importer.ReadFile(t_path, aiProcess_Triangulate | aiProcess_FlipUVs);
        // const aiScene *scene = importer.ReadFile(t_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
        // const aiScene *scene = importer.ReadFile(t_path, aiProcess_Triangulate | aiProcess_GenNormals);
        const aiScene *scene = importer.ReadFile(t_path, aiProcess_Triangulate);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            ERE_INFO("ERROR::ASSIMP::{}", importer.GetErrorString());
            return;
        }

        for (unsigned int i = 0; i < scene->mNumLights; i++) {
            aiLight* light = scene->mLights[i];

            switch (light->mType) {
            case aiLightSource_DIRECTIONAL:
                {
                    auto dir_light = std::make_shared<directional_light>(directional_light{
                        .direction = glm::vec3(light->mDirection.x, light->mDirection.y, light->mDirection.z),
                        .ambient = glm::vec3(light->mColorAmbient.r, light->mColorAmbient.g, light->mColorAmbient.b),
                        .diffuse = glm::vec3(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b),
                        .specular = glm::vec3(light->mColorSpecular.r, light->mColorSpecular.g, light->mColorSpecular.b),
                    });
                    m_light_scene->add_directional_light(dir_light);
                    break;
                }
            case aiLightSource_POINT: {
                    auto p_light = std::make_shared<point_light>(point_light{
                        .position = glm::vec3(light->mPosition.x, light->mPosition.y, light->mPosition.z),
                        .ambient = glm::vec3(light->mColorAmbient.r, light->mColorAmbient.g, light->mColorAmbient.b),
                        .diffuse = glm::vec3(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b),
                        .specular = glm::vec3(light->mColorSpecular.r, light->mColorSpecular.g, light->mColorSpecular.b),
                        .constant = light->mAttenuationConstant,
                        .linear = light->mAttenuationLinear,
                        .quadratic = light->mAttenuationQuadratic,
                    });
                    m_light_scene->add_point_light(p_light);
                    break;
                }
            case aiLightSource_SPOT: {
                    auto spotl = std::make_shared<spot_light>(spot_light{
                        .position = glm::vec3(light->mPosition.x, light->mPosition.y, light->mPosition.z),
                        .direction = glm::vec3(light->mDirection.x, light->mDirection.y, light->mDirection.z),
                        .cut_off = glm::cos(glm::radians(light->mAngleInnerCone)),
                        .outer_cut_off = glm::cos(glm::radians(light->mAngleOuterCone)),
                        .ambient = glm::vec3(light->mColorAmbient.r, light->mColorAmbient.g, light->mColorAmbient.b),
                        .diffuse = glm::vec3(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b),
                        .specular = glm::vec3(light->mColorSpecular.r, light->mColorSpecular.g, light->mColorSpecular.b),
                        .constant = light->mAttenuationConstant,
                        .linear = light->mAttenuationLinear,
                        .quadratic = light->mAttenuationQuadratic,
                    });
                    m_light_scene->add_spot_light(spotl);
                break;
                }
            default:
                break;
            }
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

        mesh m(vertices, uv, normals, indices);

        if (t_mesh->mMaterialIndex >= 0) {
            aiMaterial* material = t_secne->mMaterials[t_mesh->mMaterialIndex];
            ref<texture2d_api> diffuse_map = load_material_texture(material, aiTextureType_DIFFUSE, "texture_diffuse");
            ref<texture2d_api> specular_maps = load_material_texture(material, aiTextureType_SPECULAR, "texture_specular");

            aiColor3D k_ambient(0.0f, 0.0f, 0.0f);
            aiColor3D k_diffuse(0.0f, 0.0f, 0.0f);
            aiColor3D k_specular(0.0f, 0.0f, 0.0f);
            float shininess = 32;

            material->Get(AI_MATKEY_COLOR_AMBIENT, k_ambient);
            material->Get(AI_MATKEY_COLOR_DIFFUSE, k_diffuse);
            material->Get(AI_MATKEY_COLOR_SPECULAR, k_specular);
            material->Get(AI_MATKEY_SHININESS, shininess);

            ere::material mat = {
                .ambient = glm::vec3(k_ambient.r, k_ambient.g, k_ambient.b),
                .diffuse = glm::vec3(k_diffuse.r, k_diffuse.g, k_diffuse.b),
                .specular = glm::vec3(k_specular.r, k_specular.g, k_specular.b),
                .shininess = shininess,
                .diffuse_texture = diffuse_map,
                .specular_texture = specular_maps,
                .emission_texture = nullptr,
            };

            m.set_material(mat);
        }

        return m;
    }

    ref<texture2d_api> load_material_texture(aiMaterial* t_mat, aiTextureType t_type, const std::string& t_type_name) {
        if (t_mat->GetTextureCount(t_type) > 1) {
            ERE_INFO("WARNING::MODEL::TEXTURE::{}::{}", t_type_name, "more than one texture of the same type");
        }

        ref<texture2d_api> tex = nullptr;
        for (unsigned int i = 0; i < t_mat->GetTextureCount(t_type); i++) {
            aiString str;
            t_mat->GetTexture(t_type, i, &str);
            bool skip = false;
            for (unsigned int j = 0; j < m_textures_loaded.size(); j++) {
                if (std::strcmp(m_textures_loaded[j].path.c_str(), str.C_Str()) == 0) {
                    tex = m_textures_loaded[j].texture;
                    skip = true;
                    break;
                }
            }

            if (!skip) {
                ref<texture2d_api> texture = texture2d_api::create_texture2d_api(m_directory + "/" + str.C_Str());
                tex = texture;
                m_textures_loaded.push_back({str.C_Str(), texture});
            }
        }

        return tex;
    }

private:

    std::vector<mesh> m_meshes;
    std::string m_directory;
    std::vector<texture> m_textures_loaded;
    ref<light_scene> m_light_scene;
};


}

#endif

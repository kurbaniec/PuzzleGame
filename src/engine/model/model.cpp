//
// Created by kurbaniec on 22.12.2021.
//

#include "model.h"

#include <utility>

namespace engine {
    Model::Model(
        std::string id,
        std::function<std::shared_ptr<Instance>
            (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
    ) : id(std::move(id)), creator(std::move(creator)) {}

    std::shared_ptr<Instance>
    engine::Model::create(
        std::string instanceId,
        glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 origin
    ) {
        return creator(
            std::move(instanceId), position, rotation, scale, origin,
            boundsMin, boundsMax
        );
    }

    void Model::loadModel(
        const std::string& path, std::vector<Texture>& textures_loaded, std::vector<Mesh>& meshes,
        std::vector<Mesh>& transparentMeshes
    ) {
        // Read file via ASSIMP
        // Also generate bounding boxes
        // See: https://github.com/assimp/assimp/issues/426#issuecomment-920930875
        // And: http://assimp.sourceforge.net/lib_html/postprocess_8h.html#a64795260b95f5a4b3f3dc1be4f52e410aa4ae05f45c5682ab245cf8e87986426f
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(
            path,
            aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace | aiProcess_GenBoundingBoxes
        );
        // check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            //std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            //return;
            throw std::runtime_error(std::string("ERROR::ASSIMP:: ") + importer.GetErrorString());
        }
        // retrieve the directory path of the filepath
        auto directory = path.substr(0, path.find_last_of('/'));

        // process ASSIMP's root node recursively
        processNode(scene->mRootNode, scene, textures_loaded, meshes, transparentMeshes, directory);
    }

    void Model::processNode(
        aiNode* node, const aiScene* scene, std::vector<Texture>& textures_loaded,
        std::vector<Mesh>& meshes, std::vector<Mesh>& transparentMeshes, std::string& directory
    ) {
        // process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            // the node object only contains indices to index the actual objects in the scene.
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            // Assign/Update bounding box
            updateModelBounds(mesh);
            // Process mesh
            auto engineMesh = processMesh(mesh, scene, textures_loaded, directory);
            if (!engineMesh.transparent) {
                meshes.push_back(std::move(engineMesh));
            } else {
                transparentMeshes.push_back(std::move(engineMesh));
            }
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene, textures_loaded, meshes, transparentMeshes, directory);
        }
    }

    Mesh Model::processMesh(
        aiMesh* mesh, const aiScene* scene, std::vector<Texture>& textures_loaded,
        std::string& directory
    ) {
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            if (mesh->HasNormals()) {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;
            } else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // Also check if mesh contains transparent elements
        bool transparent = false;

        // 1. diffuse maps
        std::vector<Texture> diffuseMaps = loadMaterialTextures(
            material, aiTextureType_DIFFUSE, "texture_diffuse",
            textures_loaded, directory, transparent);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = loadMaterialTextures(
            material, aiTextureType_SPECULAR, "texture_specular",
            textures_loaded, directory, transparent);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(
            material, aiTextureType_HEIGHT, "texture_normal",
            textures_loaded, directory, transparent);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(
            material, aiTextureType_AMBIENT, "texture_height",
            textures_loaded, directory, transparent);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        /*for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            auto color = scene->mMaterials[mesh->mMaterialIndex]->mColors[0][i];
            print("Has Color ", mesh->HasVertexColors(i), " ", color);
        }*/
        //print(mesh->GetNumColorChannels());

        // return a mesh object created from the extracted mesh data
        return Mesh(vertices, indices, textures, transparent);
    }

    std::vector<Texture> Model::loadMaterialTextures(
        aiMaterial* mat, aiTextureType type, std::string typeName,
        std::vector<Texture>& textures_loaded, std::string& directory,
        bool& transparent
    ) {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded.size(); j++) {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip) {   // if texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), directory, transparent);
                texture.type = typeName;
                texture.path = str.C_Str();
                texture.transparent = transparent;
                textures.push_back(texture);
                textures_loaded.push_back(
                    texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
    }

    // See: https://stackoverflow.com/a/874160/12347616
    bool Model::hasEnding(const std::string& fullString, const std::string& ending) {
        if (fullString.length() >= ending.length()) {
            return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
        } else {
            return false;
        }
    }

    unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool& transparent) {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        if (hasEnding(filename, ".dds")) {
            // Use DDS loader
            // Notes:
            // * Requires flipped image!
            // * Supports only DXT1/2/3/4/5 formats (a.k.a BC1/2/3)
            // * The rest of the (SOIL2) flags with the exception of SOIL_FLAG_TEXTURE_REPEATS will be ignored while
            //	 loading already-compressed DDS files
            // See: https://github.com/SpartanJ/SOIL2
            // And: https://www.reedbeta.com/blog/understanding-bcn-texture-compression-formats/#bc2-bc3-and-bc5
            textureID = SOIL_load_OGL_texture(
                filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_TEXTURE_REPEATS
            );
        } else {
            // Use general image loader
            // See: https://github.com/SpartanJ/SOIL2
            // And: https://github.com/alelievr/SOIL2/blob/master/incs/SOIL2.h
            textureID = SOIL_load_OGL_texture(
                filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
            );
        }

        if (textureID == 0) {
            std::cout << "Error loading texture" << std::endl;
            throw std::runtime_error("Error loading texture");
        }

        if (!transparent) {
            // Get texture dimensions
            // See: https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetTexLevelParameter.xhtml
            // And: https://stackoverflow.com/a/30141975/12347616
            // And: https://stackoverflow.com/a/10769481/12347616
            int texDims[2];
            glBindTexture(GL_TEXTURE_2D, textureID);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH,
                                     &texDims[0]);   // 0 Mipmap Level => 0 = Base image
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texDims[1]);
            //print("size ", texDims[0], "-", texDims[1]);
            // Get colors
            // See: https://stackoverflow.com/questions/48938930/pixel-access-with-glgetteximage
            auto size = texDims[0] * texDims[1] * 4;
            auto* pixels = new float[size];
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, pixels);
            // auto r = pixels[0];
            // auto g = pixels[0 + 0 + 1];
            // auto b = pixels[0 + 0 + 2];
            // auto a = pixels[0 + 0 + 3];
            //bool isTransparent = false;
            for (auto i = 0; i < size; i += 4) {
                if (pixels[i] == 1.0f) {
                    //isTransparent = true;
                    transparent = true;
                    break;
                }
            }
            glActiveTexture(GL_TEXTURE0);
            //print("transparent ", transparent);

            delete[] pixels;
        }

        return textureID;
    }

    void Model::updateModelBounds(aiMesh* mesh) {
        auto min = mesh->mAABB.mMin;
        auto max = mesh->mAABB.mMax;
        if (min.x < boundsMin.x) boundsMin.x = min.x;
        if (min.y < boundsMin.y) boundsMin.y = min.y;
        if (min.z < boundsMin.z) boundsMin.z = min.z;
        if (max.x > boundsMax.x) boundsMax.x = max.x;
        if (max.y > boundsMax.y) boundsMax.y = max.y;
        if (max.z > boundsMax.z) boundsMax.z = max.z;
    }

    glm::vec3 Model::boundingBoxMin() {
        return boundsMin;
    }

    glm::vec3 Model::boundingBoxMax() {
        return boundsMax;
    }


}

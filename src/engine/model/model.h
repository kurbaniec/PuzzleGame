//
// Created by kurbaniec on 17.12.2021.
//

#ifndef PUZZLE_GAME_ENGINE_MODEL_H
#define PUZZLE_GAME_ENGINE_MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <stb_image.h>
#include <SOIL2.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <functional>
#include "shader.h"
#include "mesh.h"
#include "../instance/instance.h"
#include "triangle.h"

namespace engine {
    // Forward declaration
    // See: https://stackoverflow.com/a/35452830/12347616
    class Instance;

    class Triangle;

    class Model {
    public:
        const std::string id;

        explicit Model(
            std::string id,
            std::function<std::shared_ptr<Instance>
                (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
        );

        virtual void drawInstances(glm::mat4 view, glm::mat4 projection) = 0;

        virtual std::vector<std::reference_wrapper<Triangle>> getTriangles() = 0;

        virtual std::shared_ptr<Instance> create(
            std::string instanceId,
            glm::vec3 position,
            glm::vec3 rotation,
            glm::vec3 scale,
            glm::vec3 origin
        );

        glm::vec3 boundingBoxMin();
        glm::vec3 boundingBoxMax();

    protected:
        // Local Bounding Box / AABB coordinates
        glm::vec3 boundsMin{};
        glm::vec3 boundsMax{};

        // Instance Creator
        std::function<std::shared_ptr<Instance>(
            std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3
        )> creator;

        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(
            std::string const& path,
            std::vector<Texture>& textures_loaded,
            std::vector<Mesh>& meshes,
            std::vector<Mesh>& transparentMeshes
        );

        void updateModelBounds(aiMesh* mesh);

    private:
        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(
            aiNode* node,
            const aiScene* scene,
            std::vector<Texture>& textures_loaded,
            std::vector<Mesh>& meshes,
            std::vector<Mesh>& transparentMeshes,
            std::string& directory
        );

        Mesh processMesh(
            aiMesh* mesh,
            const aiScene* scene,
            std::vector<Texture>& textures_loaded,
            std::string& directory
        );

        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a Texture struct.
        std::vector<Texture> loadMaterialTextures(
            aiMaterial* mat,
            aiTextureType type,
            std::string typeName,
            std::vector<Texture>& textures_loaded,
            std::string& directory,
            bool& transparent
        );

        // See: https://stackoverflow.com/a/874160/12347616
        bool hasEnding(std::string const& fullString, std::string const& ending);

        unsigned int TextureFromFile(const char* path, const std::string& directory, bool& transparent);
    };
}

#endif //PUZZLE_GAME_ENGINE_MODEL_H

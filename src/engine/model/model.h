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

namespace engine {
    // Forward declaration
    // See: https://stackoverflow.com/a/35452830/12347616
    class Instance;

    //unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

    class Model {
    public:
        const std::string id;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::vec3 origin;

        // model data
        /*vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh> meshes;
        string directory;*/
        explicit Model(
            std::string id,
            std::shared_ptr<Shader> shader,
            std::function<std::shared_ptr<Instance>
                (std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator
        );

        // draws the model, and thus all its meshes
        /*void Draw(Shader& shader) {
            //print("Mesh size: ", meshes.size());
            for (unsigned int i = 0; i < meshes.size(); i++)
                meshes[i].Draw(shader);
        }*/
        virtual void draw(glm::mat4 view, glm::mat4 projection) = 0;

        virtual glm::mat4 getModelMatrix() = 0;

        virtual std::shared_ptr<Instance> create(
            std::string id,
            glm::vec3 position,
            glm::vec3 rotation,
            glm::vec3 scale,
            glm::vec3 origin
        );

    protected:
        glm::mat4 modelMatrix;
        std::shared_ptr<Shader> shader;
        std::function<std::shared_ptr<Instance>(std::string, glm::vec3, glm::vec3, glm::vec3, glm::vec3)> creator;

        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(
            std::string const& path,
            std::vector<Texture>& textures_loaded,
            std::vector<Mesh>& meshes
        );

    private:
        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(
            aiNode* node,
            const aiScene* scene,
            std::vector<Texture>& textures_loaded,
            std::vector<Mesh>& meshes,
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

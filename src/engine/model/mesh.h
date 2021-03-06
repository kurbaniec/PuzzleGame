//
// Source: https://learnopengl.com/Model-Loading/Model
//

#ifndef PUZZLE_GAME_ENGINE_MESH_H
#define PUZZLE_GAME_ENGINE_MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "../../utils/print.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

namespace engine {

    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
        bool transparent;
    };

    class Mesh {
    public:
        // mesh Data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        // const bool transparent;
        bool transparent;
        unsigned int VAO;

        // constructor
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, bool transparent);

        // render the mesh
        void draw(std::shared_ptr<Shader> const& shader);

        // render subpart (triangle) of the mesh
        void drawTriangle(std::shared_ptr<Shader> const& shader, unsigned int offset);

    private:
        // render data
        unsigned int VBO, EBO;

        void bindTexture(const std::shared_ptr<Shader>& shader);

        void unbindTexture();

        // initializes all the buffer objects/arrays
        void setupMesh();
    };
}

#endif //PUZZLE_GAME_ENGINE_MESH_H
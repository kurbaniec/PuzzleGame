//
// Created by kurbaniec on 21.12.2021.
//

#ifndef PUZZLE_GAME_SIMPLEMODEL_H
#define PUZZLE_GAME_SIMPLEMODEL_H


#include "model.h"

class SimpleModel : public Model {
public:
    // model data
    std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;

    // constructor, expects a filepath to a 3D model.
    explicit SimpleModel(const std::string& path, std::shared_ptr<Shader> shader);

    void draw() override;
};


#endif //PUZZLE_GAME_SIMPLEMODEL_H

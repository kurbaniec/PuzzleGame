//
// Created by kurbaniec on 21.12.2021.
//

#ifndef PUZZLE_GAME_SIMPLEMODEL_H
#define PUZZLE_GAME_SIMPLEMODEL_H


#include "model.h"

class SimpleModel : public Model {
public:
// model data
    vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    SimpleModel(const string& path1, bool gamma1, string
    const& path, bool gamma = false) {
        loadModel(path);
    }
};


#endif //PUZZLE_GAME_SIMPLEMODEL_H

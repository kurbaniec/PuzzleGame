//
// Created by kurbaniec on 21.12.2021.
//

#include "simplemodel.h"

namespace engine {

    SimpleModel::SimpleModel(
            const std::string& path,
            std::shared_ptr<Shader> shader
    ) : Model(std::move(shader)) {
        loadModel(path, textures_loaded, meshes);
    }

    void SimpleModel::draw() {
        shader->use();
        for (auto& mesh: meshes)
            mesh.Draw(shader);
    }

}

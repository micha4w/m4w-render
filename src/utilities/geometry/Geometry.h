#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace m4w {

    struct Rect {
        glm::vec2 corner;
        glm::vec2 size;
    };

    struct Cube {
        glm::vec3 corner;
        glm::vec3 size;
    };
}
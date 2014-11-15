#ifndef MODEL_ANIMATIONCONTAINER_H
#define MODEL_ANIMATIONCONTAINER_H

#include <vector>
#include <ctime>

#include "Model.FieldPosition.h"

namespace model{

struct AnimationContainer{

    std::vector<model::FieldPosition> objects;
    timespec timestamp;

};
}

#endif // MODEL_ANIMATIONCONTAINER_H

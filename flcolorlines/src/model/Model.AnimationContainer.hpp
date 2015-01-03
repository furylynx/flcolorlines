#ifndef MODEL_ANIMATIONCONTAINER_H
#define MODEL_ANIMATIONCONTAINER_H

//custom includes
#include "Model.FieldPosition.hpp"

//global includes
#include <vector>
#include <ctime>


namespace model
{

struct AnimationContainer
{

    std::vector<model::FieldPosition> objects;
    timespec timestamp;

};

}//namespace model

#endif // MODEL_ANIMATIONCONTAINER_H

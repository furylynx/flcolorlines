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
    /**
     * The field position objects.
     */
    std::vector<model::FieldPosition> objects;

    /**
     * The beginning timestamp.
     */
    timeval timestamp;

};

}//namespace model

#endif // MODEL_ANIMATIONCONTAINER_H

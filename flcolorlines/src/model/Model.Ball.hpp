#ifndef MODEL_BALL_CPP
#define MODEL_BALL_CPP

//custom includes
#include "Model.Color.hpp"

//global includes
#include <string>
#include <sstream>
#include <string>
#include <iostream>


namespace model
{

struct Ball
{
    /**
     * The color of the ball.
     */
    Color color;

    /**
     * The flag for an invalid ball. Per default to be set to false.
     */
    bool isNull;

    /**
     * The flag for an out of the field ball. Per default to be set to false.
     */
    bool outOfField;

    /**
     * Returns the string representation of the object.
     *
     * @return The string representation.
     */
    std::string toString() const;
};

}//namespace model

#endif // MODEL_BALL_CPP

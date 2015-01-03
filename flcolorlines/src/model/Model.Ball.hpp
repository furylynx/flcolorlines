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
        Color color;
        bool isNull; // = false;
        bool outOfField; // = false;

        std::string toString() const;
};

}//namespace model

#endif // MODEL_BALL_CPP

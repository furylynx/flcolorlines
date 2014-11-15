#ifndef MODEL_BALL_CPP
#define MODEL_BALL_CPP

#include <string>

#include "Model.Color.h"

namespace model{

struct Ball{

        Color color;
        bool isNull; // = false;
        bool outOfField; // = false;

        std::string toString() const;

};
}
#endif // MODEL_BALL_CPP

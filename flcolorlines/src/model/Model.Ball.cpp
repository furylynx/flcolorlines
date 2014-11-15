#include <sstream>
#include <string>
#include <iostream>

#include "Model.Ball.h"

using namespace model;

std::string Ball::toString() const{

    std::ostringstream ret;
    ret << "(color: "<< color.color << ", null: " << isNull << ", out of field: " << outOfField << ")";

    return ret.str();
}

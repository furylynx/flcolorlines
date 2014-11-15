#include <sstream>
#include <string>
#include <iostream>

#include "Model.FieldPosition.h"

using namespace model;

std::string FieldPosition::toString() const{

    std::ostringstream ret;
    ret << "("<<posX << "," << posY << ")";

    return ret.str();
}

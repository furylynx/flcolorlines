#include "Model.FieldPosition.hpp"

using namespace model;

std::string FieldPosition::toString() const{

    std::ostringstream ret;
    ret << "("<<posX << "," << posY << ")";

    return ret.str();
}

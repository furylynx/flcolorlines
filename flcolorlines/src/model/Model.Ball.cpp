#include "Model.Ball.hpp"

using namespace model;

std::string Ball::toString() const{

    std::ostringstream ret;
    ret << "(color: "<< color.color << ", null: " << isNull << ", out of field: " << outOfField << ")";

    return ret.str();
}

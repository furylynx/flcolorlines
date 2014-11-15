#ifndef MODEL_FIELDPOSITION_H
#define MODEL_FIELDPOSITION_H

#include <string>

namespace model{

struct FieldPosition{

    int posX;
    int posY;

    std::string toString() const;

};

}

#endif // MODEL_FIELDPOSITION_H

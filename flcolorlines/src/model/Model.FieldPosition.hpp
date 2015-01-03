#ifndef MODEL_FIELDPOSITION_H
#define MODEL_FIELDPOSITION_H

//custom includes
//...

//global includes
#include <string>
#include <sstream>
#include <string>
#include <iostream>


namespace model
{

struct FieldPosition
{

    int posX;
    int posY;

    std::string toString() const;

};

}//namespace model

#endif // MODEL_FIELDPOSITION_H

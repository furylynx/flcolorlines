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
    /**
     * The x-position.
     */
    int posX;

    /**
     * The y-position.
     */
    int posY;

    /**
     * Returns the string representation of the object.
     *
     * @return The string representation.
     */
    std::string toString() const;

};

}//namespace model

#endif // MODEL_FIELDPOSITION_H

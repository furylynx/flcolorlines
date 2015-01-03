#ifndef MODEL_GAMEACTION_H
#define MODEL_GAMEACTION_H

//custom includes
#include "Model.FieldPosition.hpp"

//global includes
//...

namespace model
{

struct GameAction
{
    enum ActionType{ADDBALL,REMOVEBALL,INCREMENTSCORE,NEWTURN,NONE} type;
    unsigned int value;//color if add or remove ball, points if score incremented
    model::FieldPosition pos;

};

}//namespace model

#endif // MODEL_GAMEACTION_H

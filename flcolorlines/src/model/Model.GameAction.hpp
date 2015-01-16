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
    /**
     * The type of the action.
     */
    enum ActionType{ADDBALL,REMOVEBALL,INCREMENTSCORE,NEWTURN,NONE} type;

    /**
     * The value can be a color if the action is ADDBALL or REMOVEBALL. If INCREMENTSCORE the value is the score.
     */
    unsigned int value;

    /**
     * The field position.
     */
    model::FieldPosition pos;

};

}//namespace model

#endif // MODEL_GAMEACTION_H

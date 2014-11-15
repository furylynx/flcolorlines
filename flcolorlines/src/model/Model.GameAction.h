#ifndef MODEL_GAMEACTION_H
#define MODEL_GAMEACTION_H

#include "Model.FieldPosition.h"

namespace model{
struct GameAction{

    enum ActionType{ADDBALL,REMOVEBALL,INCREMENTSCORE,NEWTURN,NONE} type;
    unsigned int value;//color if add or remove ball, points if score incremented
    model::FieldPosition pos;

};

}

#endif // MODEL_GAMEACTION_H

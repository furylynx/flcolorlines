#ifndef CONTROLLER_GAMEACTIONCONTROLLER_H
#define CONTROLLER_GAMEACTIONCONTROLLER_H

#include "Model.GameAction.h"
#include "Model.GameField.h"

namespace controller{
class GameActionController{

public:

    GameActionController();
    ~GameActionController();

    void setOptions(model::GameField* field);

    void addAction(model::GameAction action);
    model::GameAction undoLastAction();
    int undoLastTurn(); //returns the score to be reset

    model::GameAction redoLastAction();
    int redoLastTurn();

    void clear();

    bool undoPossible() const;
    bool redoPossible() const;

private:
    std::vector<model::GameAction> actions;
    std::vector<model::GameAction> redoActions;
    model::GameField* theField;

};
}

#endif // CONTROLLER_GAMEACTIONCONTROLLER_H

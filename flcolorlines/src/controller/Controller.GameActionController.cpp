#include "Controller.GameActionController.h"

using namespace controller;

GameActionController::GameActionController(){
}

GameActionController::~GameActionController(){

}

void GameActionController::setOptions(model::GameField* field){
    theField = field;
}

void GameActionController::clear(){
    actions.clear();
    redoActions.clear();
}

void GameActionController::addAction(model::GameAction action){
    actions.push_back(action);
    redoActions.clear();
}

model::GameAction GameActionController::undoLastAction(){

    if (!undoPossible()){
        model::GameAction action;
        action.type = model::GameAction::NONE;
        return action;
    }

    model::GameAction lastAction = actions[actions.size()-1];
    actions.pop_back();

    if (lastAction.type == model::GameAction::ADDBALL)
        theField->removeBallAt(lastAction.pos);

    if (lastAction.type == model::GameAction::REMOVEBALL){
        model::Ball ball;
        ball.isNull = false;
        ball.color.color = lastAction.value;
        theField->setBallAt(lastAction.pos, ball);
    }

    //Do nothing in case of new turn

    redoActions.push_back(lastAction);

    return lastAction;
}

int GameActionController::undoLastTurn(){

    model::GameAction lastAction = undoLastAction();

    if (lastAction.type == model::GameAction::NEWTURN || lastAction.type == model::GameAction::NONE)
        return 0;

    int scorecount = 0;

    while( lastAction.type != model::GameAction::NEWTURN && lastAction.type != model::GameAction::NONE)
    {
        if (lastAction.type == model::GameAction::INCREMENTSCORE){
            scorecount += (int)lastAction.value;
        }

        lastAction = undoLastAction();
    }

    return scorecount;
}


bool GameActionController::undoPossible() const{

    bool undoPossibleB = false;

    for (int i = 0; i < actions.size(); i++)
        if (actions[i].type == model::GameAction::NEWTURN)
            undoPossibleB = true;

    return undoPossibleB;

}

model::GameAction GameActionController::redoLastAction(){

    if (!redoPossible()){
        model::GameAction action;
        action.type = model::GameAction::NONE;
        return action;
    }

    model::GameAction lastAction = redoActions[redoActions.size()-1];
    redoActions.pop_back();

    if (lastAction.type == model::GameAction::ADDBALL){
        model::Ball ball;
        ball.isNull = false;
        ball.color.color = lastAction.value;
        theField->setBallAt(lastAction.pos, ball);
    }

    if (lastAction.type == model::GameAction::REMOVEBALL){
        theField->removeBallAt(lastAction.pos);
    }

    //Do nothing in case of new turn

    actions.push_back(lastAction);

    return lastAction;
}

int GameActionController::redoLastTurn(){

    model::GameAction lastAction;

    for (int i = 0; i<2; i++){
        lastAction = redoLastAction();

        if (lastAction.type == model::GameAction::NONE)
            return 0;
    }

    int scorecount = 0;

    while( lastAction.type != model::GameAction::NEWTURN && lastAction.type != model::GameAction::NONE)
    {
        if (lastAction.type == model::GameAction::INCREMENTSCORE){
            scorecount += (int)lastAction.value;
        }

        lastAction = redoLastAction();
    }

    //undoLastAction();

    return scorecount;
}

bool GameActionController::redoPossible() const{

    return (redoActions.size() > 0);
}

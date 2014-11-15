#include <iostream>
#include <cstdlib>
#include <assert.h>

#include "Controller.GameController.h"


using namespace controller;

GameController::GameController(){
    theField = 0;
    actionController = new controller::GameActionController();
}

GameController::~GameController(){
    delete theField;
    delete actionController;
}


void GameController::setOptions(int dimx, int dimy, int amount_colors, int amount_newballs, int amount_line){
    actionController->setOptions(0);

    if (theField != 0)
        delete theField;

    theField = new model::GameField(dimx, dimy);
    actionController->setOptions(theField);


    this->amount_colors = amount_colors;
    this->amount_newballs = amount_newballs;
    this->amount_line = amount_line;

    optionsSet = true;
}

bool GameController::areOptionsSet(){
    return optionsSet;
}

void GameController::startNewMatch(){

    if (!optionsSet){
        std::cerr << "No options defined, default used.";

        actionController->setOptions(0);
        //delete theField;
        theField = new model::GameField(9, 9);
        actionController->setOptions(theField);
    }

    theScore = 0;
    theField->clear();
    if(actionController != 0)
        actionController->clear();


//    //TODO REMOVE!!!
//    model::FieldPosition pos;
//    pos.posX = 0;
//    pos.posY = 1;
//    model::Ball ball;
//    ball.color.setColor(model::Color::BLUE);
//    theField->setBallAt(pos,ball);
//    pos.posX = 1;
//    theField->setBallAt(pos,ball);
//    pos.posX = 2;
//    theField->setBallAt(pos,ball);
//    pos.posX = 3;
//    theField->setBallAt(pos,ball);

//    pos.posX = 5;
//    theField->setBallAt(pos,ball);
//    //---

    generateRandomBalls(amount_newballs);

}

void GameController::decreaseScore(int c){
    theScore -= c;
}

void GameController::increaseScore(int c){
    increaseScore(c,true);
}

void GameController::increaseScore(int c, bool logAction){

    model::GameAction action;
    action.type = model::GameAction::INCREMENTSCORE;
    action.value = (unsigned int) c;

    if (actionController != 0 && logAction)
        actionController->addAction(action);

    theScore += c;
}

std::vector<model::FieldPosition> GameController::getPath(model::FieldPosition pos1, model::FieldPosition pos2) const{

    std::vector<model::FieldPosition> ret = theField->getPath(pos1,pos2);

    return ret;
}

bool GameController::moveBallForce(model::FieldPosition pos1, model::FieldPosition pos2){

    if (!theField->getBallAt(pos2).isNull || theField->getBallAt(pos2).outOfField)
        return false;

    model::GameAction action3;
    action3.type = model::GameAction::NEWTURN;
    if (actionController != 0)
        actionController->addAction(action3);

    //switch ball to position
    model::Ball ball = theField->getBallAt(pos1);
    theField->setBallAt(pos2, ball);
    theField->removeBallAt(pos1);

    //log actions
    model::GameAction action;
    action.type = model::GameAction::ADDBALL;
    action.pos = pos2;
    action.value = ball.color.color;
    if (actionController != 0)
        actionController->addAction(action);

    model::GameAction action2;
    action2.type = model::GameAction::REMOVEBALL;
    action2.value = ball.color.color;
    action2.pos = pos1;
    if (actionController != 0)
        actionController->addAction(action2);

    lastRemovedBalls.clear();
    if (!checkLines(pos2))
        generateRandomBalls(amount_newballs);
    else
        lastGeneratedBalls.clear();

    return true;

}

bool GameController::checkLines(model::FieldPosition pos){

    std::vector<model::Ball> neighbours = theField->getNeighbours(pos);
    std::vector<int> counters;

    //count number of balls with same color in each direction
    for (int i = model::GameField::Topleft ; i <= model::GameField::BottomRight; i++)
    {
        counters.push_back(0);

        if (i == model::GameField::Middle)
            ;//do nothing cause this is no neighbour
        else{
            if (!neighbours[i].isNull && !neighbours[i].outOfField && neighbours[i].color == neighbours[model::GameField::Middle].color){

                model::FieldPosition npos = model::GameField::getPositionOfNeighbour(pos, static_cast<model::GameField::Neighbour>(i));
                counters[i]++;

                while (!theField->getNeighbourAt(npos,static_cast<model::GameField::Neighbour>(i)).isNull && !theField->getNeighbourAt(npos,static_cast<model::GameField::Neighbour>(i)).outOfField && theField->getNeighbourAt(npos,static_cast<model::GameField::Neighbour>(i)).color == theField->getNeighbourAt(pos,static_cast<model::GameField::Neighbour>(i)).color){
                    counters[i]++;

                    npos = model::GameField::getPositionOfNeighbour(npos, static_cast<model::GameField::Neighbour>(i));

                }
            }


        }
    }

//    std::cout << counters[0] << ", " << counters[1] << ", " << counters[2] << ", " << counters[3] << ", " << counters[5] << ", " << counters[6] << ", " << counters[7] << ", " << counters[8] <<"\n";

    //check for lines longer than the set amount
    bool anyLineExistent = false;

    for(int i=model::GameField::Topleft; i <= (int)(model::GameField::BottomRight/2); i++){

        if (counters[i]+1+counters[model::GameField::BottomRight-i] >= amount_line){
            anyLineExistent = true;

            //remove balls
            model::FieldPosition npos = model::GameField::getPositionOfNeighbour(pos, static_cast<model::GameField::Neighbour>(i));
            for (int j = 1; j<= counters[i];j++){
                model::Ball b = theField->removeBallAt(npos);
                lastRemovedBalls.push_back(npos);

                model::GameAction action;
                action.type = model::GameAction::REMOVEBALL;
                action.pos = npos;
                action.value = b.color.color;
                if (actionController != 0)
                    actionController->addAction(action);

                npos = model::GameField::getPositionOfNeighbour(npos, static_cast<model::GameField::Neighbour>(i));
            }

            npos = model::GameField::getPositionOfNeighbour(pos, static_cast<model::GameField::Neighbour>(model::GameField::BottomRight-i));
            for (int j = 1; j<= counters[model::GameField::BottomRight-i];j++){
                model::Ball b = theField->removeBallAt(npos);
                lastRemovedBalls.push_back(npos);

                model::GameAction action;
                action.type = model::GameAction::REMOVEBALL;
                action.pos = npos;
                action.value = b.color.color;
                if (actionController != 0)
                    actionController->addAction(action);

                npos = model::GameField::getPositionOfNeighbour(npos, static_cast<model::GameField::Neighbour>(model::GameField::BottomRight-i));
            }
        }
    }

    if (anyLineExistent){
        model::Ball b = theField->removeBallAt(pos);
        lastRemovedBalls.push_back(pos);

        model::GameAction action;
        action.type = model::GameAction::REMOVEBALL;
        action.pos = pos;
        action.value = b.color.color;
        if (actionController != 0)
            actionController->addAction(action);
    }
    else
        return false;

    //count scores
    int scoreinc = 1;

    for(int i=model::GameField::Topleft; i <= (int)(model::GameField::BottomRight/2); i++)
        scoreinc += counters[i]+counters[model::GameField::BottomRight-i];

    increaseScore(scoreinc*scoreinc);//increase score by amount of removed balls squared

    return true;
}

std::vector<model::FieldPosition> GameController::moveBall(model::FieldPosition pos1, model::FieldPosition pos2){

    std::vector<model::FieldPosition> path = getPath(pos1, pos2);

    if (path[path.size()-1].posX == pos2.posX && path[path.size()-1].posY == pos2.posY){
           moveBallForce(pos1,pos2);
    }


    return path;
}

bool GameController::generateRandomBalls(int n){


    lastGeneratedBalls.clear();
    std::vector<model::FieldPosition> freePos = theField->getEmptyFields();

    if (freePos.size() == 0)
    {
        //todo: game over!

        return true;
    }

    for (int i = 0; i<n;i++){

        model::FieldPosition pos;

        //random pos
        int el = rand() % freePos.size();//rand number between zero and the number of free fields minus 1

        pos = freePos[el];

        //random color
        int col = rand() % amount_colors;

        if (amount_colors > model::Color::AMOUNT_DEFINED_COLORS)
            assert(false);//TODO do something to catch this

        //set color for the ball
        model::Color color;
        color.setColor(static_cast<model::Color::DefinedColor>(col));

        model::Ball b;
        b.isNull = false;
        b.outOfField = false;
        b.color = color;

        //add ball to field
        theField->setBallAt(pos,b);

        model::GameAction action;
        action.type = model::GameAction::ADDBALL;
        action.pos = pos;
        action.value = b.color.color;

        if (actionController != 0)
            actionController->addAction(action);

        checkLines(pos);
        freePos = theField->getEmptyFields();

        lastGeneratedBalls.push_back(pos);

        if (freePos.size() == 0)
        {
            //todo: game over!

            return true;
        }

    }

    return false;
}

bool GameController::undoLastTurn(){
    if (actionController != 0){
        decreaseScore(actionController->undoLastTurn());
        return actionController->undoPossible();
    }
    else
        return false;
}

bool GameController::redoLastTurn(){
    if (actionController != 0 && ! isGameOver()){
        increaseScore(actionController->redoLastTurn(), false);
        return actionController->redoPossible();
    }
    else
        return false;
}

bool GameController::undoPossible(){
    if (actionController != 0 && ! isGameOver()){
        return actionController->undoPossible();
    }else
        return false;
}

bool GameController::redoPossible(){
    if (actionController != 0){
        return actionController->redoPossible();
    }else
        return false;
}

model::GameField* GameController::getGameField() const{
    return theField;
}

int GameController::getTheScore() const{
    return theScore;
}

bool GameController::isGameOver() const{
    if (theField == 0)
        return true;

    return theField->getEmptyFields().size() == 0;
}

int GameController::getAmountColors() const{
    return amount_colors;
}

int GameController::getAmountNewBalls() const{
    return amount_newballs;
}

int GameController::getAmountLine() const{
    return amount_line;
}


std::vector<model::FieldPosition> GameController::getLastGeneratedBalls(){
    return lastGeneratedBalls;
}

std::vector<model::FieldPosition> GameController::getLastRemovedBalls(){
    return lastRemovedBalls;
}

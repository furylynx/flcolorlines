#ifndef CONTROLLER_GAMECONTROLLER_H
#define CONTROLLER_GAMECONTROLLER_H

//custom includes
#include "../model/Model.GameField.hpp"
#include "Controller.GameActionController.hpp"

//global includes
#include <iostream>
#include <cstdlib>
#include <assert.h>

namespace controller
{

class GameController
{

public:

    GameController();
    ~GameController();

    void setOptions(int dimx, int dimy, int amount_colors, int amount_newballs, int amount_line);
    bool areOptionsSet();

    void startNewMatch();//counter to zero, new game field

    std::vector<model::FieldPosition> getPath(model::FieldPosition pos1, model::FieldPosition pos2) const;//if vector doesn't contain pos2 there is no path
    std::vector<model::FieldPosition> moveBall(model::FieldPosition pos1, model::FieldPosition pos2); // if vector does't contain pos2 the ball was not moved

    bool moveBallForce(model::FieldPosition pos1, model::FieldPosition pos2);//just moves a ball without taking account of possible ways

    bool undoLastTurn(); // rearranges the first three balls if first turn ??
    bool redoLastTurn();

    bool undoPossible();
    bool redoPossible();

    void increaseScore(int c);
    void increaseScore(int c, bool logAction);
    void decreaseScore(int c);

    model::GameField* getGameField() const;
    int getTheScore() const;
    int getAmountColors() const;
    int getAmountNewBalls() const;
    int getAmountLine() const;

    bool isGameOver() const;

    std::vector<model::FieldPosition> getLastGeneratedBalls();
    std::vector<model::FieldPosition> getLastRemovedBalls();


private:
    int amount_colors;
    int amount_newballs;
    int amount_line;

    int rounds;
    model::GameField* theField;

    std::vector<model::FieldPosition> lastGeneratedBalls;
    std::vector<model::FieldPosition> lastRemovedBalls;

    controller::GameActionController* actionController;

    int theScore;
    bool optionsSet;

    bool generateRandomBalls(int amount); // creates amount of balls at random positions, if this is not possible, the game ends
    bool checkLines(model::FieldPosition pos); //checks for Lines to remove and returns true if any; counts scores


};

}//namespace controller

#endif // CONTROLLER_GAMECONTROLLER_H

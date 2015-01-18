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

    /**
     * Creates a new game controller.
     */
    GameController();
    virtual ~GameController();

    /**
     * Sets the options for the current game.
     *
     * @param dimx Field dimension on the x-axis.
     * @param dimy Field dimension on the y-axis.
     * @param amount_colors The number of colors used for the balls.
     * @param amount_newballs The number of additional balls dropping on a move.
     * @param amount_line The number of same colored balls in a line required to remove it.
     */
    virtual void setOptions(int dimx, int dimy, int amountColors, int amountNewBalls, int amountLine);

    /**
     * Returns true if the options are set.
     *
     * @return True if set.
     */
    virtual bool areOptionsSet();

    /**
     * Starts a new game. Sets the counter to zero and sets up a new game field.
     */
    virtual void startNewMatch();

    /**
     * Returns the shortest possible path between the two field positions.
     *
     * @param pos1 The first position.
     * @param pos2 The second position.
     * @return The path.
     */
    virtual std::vector<model::FieldPosition> getPath(model::FieldPosition pos1, model::FieldPosition pos2) const;//if vector doesn't contain pos2 there is no path

    /**
     * Moves the ball from the first to the second position.
     *
     * @param pos1 The first position.
     * @param pos2 The second position.
     * @return The path. If the vector does not contain the second position, the ball was not moved.
     */
    virtual std::vector<model::FieldPosition> moveBall(model::FieldPosition pos1, model::FieldPosition pos2);

    /**
     * Forces to move the ball from the first position to the second position even if no path is available.
     *
     * @param pos1 The first position.
     * @param pos2 The second position.
     * @return True if the movement was possible in terms of having a ball moving a an empty field position.
     */
    virtual bool moveBallForce(model::FieldPosition pos1, model::FieldPosition pos2);

    /**
     * Undoes the last turn.
     *
     * @return True if further undo is possible.
     */
    virtual bool undoLastTurn();

    /**
     * Redoes the last undone turn.
     *
     * @return True if further redo is possible.
     */
    virtual bool redoLastTurn();

    /**
     * Check whether further undo is possible.
     *
     * @return True if further undo is possible.
     */
    virtual bool undoPossible();

    /**
     * Check whether further redo is possible.
     *
     * @return True if further redo is possible.
     */
    virtual bool redoPossible();

    /**
     * Increase the score by the given value.
     *
     * @param c The amount to increase.
     */
    void increaseScore(int c);

    /**
     * Increase the score by the given value. Additionally, the action is logged if the value is set.
     *
     * @param c The amount to increase.
     * @param logAction True if the action is intended to be logged.
     */
    void increaseScore(int c, bool logAction);

    /**
     * Decreases the score by the given value.
     *
     * @param c The amount to decrease.
     */
    void decreaseScore(int c);

    /**
     * Returns the game field.
     *
     * @return The game field.
     */
    virtual model::GameField* getGameField() const;


    /**
     * Returns the current score.
     *
     * @return The score.
     */
    virtual int getTheScore() const;

    /**
     * Returns the applied amount of colors.
     *
     * @return The number of colors.
     */
    virtual int getAmountColors() const;

    /**
     * Returns the amount of new balls on each turn.
     *
     * @return The number of new balls.
     */
    virtual int getAmountNewBalls() const;

    /**
     * Returns the number of balls of the same color that are required to complete a line.
     *
     * @return The number of balls.
     */
    virtual int getAmountLine() const;

    /**
     * Checks whether the game is over.
     *
     * @return True if the game is over.
     */
    virtual bool isGameOver() const;

    /**
     * Returns the recently generated new balls.
     *
     * @return The last generated balls.
     */
    virtual std::vector<model::FieldPosition> getLastGeneratedBalls();

    /**
     * Returns the recently removed balls.
     *
     * @return The last removed balls.
     */
    virtual std::vector<model::FieldPosition> getLastRemovedBalls();


private:
    /**
     * The number of different colors.
     */
    int amountColors;

    /**
     * The number of new balls on each turn.
     */
    int amountNewBalls;

    /**
     * The number of balls required for a line.
     */
    int amountLine;

    /**
     * The current number of turns.
     */
    int rounds;

    /**
     * A pointer to the game field.
     */
    model::GameField* theField;

    /**
     * The last generated balls.
     */
    std::vector<model::FieldPosition> lastGeneratedBalls;

    /**
     * The last removed balls.
     */
    std::vector<model::FieldPosition> lastRemovedBalls;

    /**
     * A pointer to the game controller.
     */
    controller::GameActionController* actionController;

    /**
     * The game score.
     */
    int theScore;

    /**
     * Flag for option set. True if the options are already set, false otherwise.
     */
    bool optionsSet;

    /**
     * Creates random balls at random, yet possible field positions. If this is not possible, the game ends.
     *
     * @param amount The number of new balls to be created.
     * @return True if the game is over.
     */
    bool generateRandomBalls(int amount);

    /**
     * Checks for Lines to be removed and returns true if there are any. Additionally, the score is increased.
     *
     * @param pos The field position to be checked. This should be the position of each newly generated ball and the destination of a moved ball.
     * @return True if there are lined to be removed.
     */
    bool checkLines(model::FieldPosition pos);


};

}//namespace controller

#endif // CONTROLLER_GAMECONTROLLER_H

#ifndef CONTROLLER_GAMEACTIONCONTROLLER_H
#define CONTROLLER_GAMEACTIONCONTROLLER_H

//custom includes
#include "../model/Model.GameAction.hpp"
#include "../model/Model.GameField.hpp"

//global includes

namespace controller
{

class GameActionController
{

public:

    /**
     * Creates a new game action controller.
     */
    GameActionController();
    virtual ~GameActionController();

    /**
     * Sets the options using the game field.
     *
     * @param field The game field.
     */
    virtual void setOptions(model::GameField* field);

    /**
     * Adds a new game action.
     *
     * @param action The game action.
     */
    virtual void addAction(model::GameAction action);

    /**
     * Undoes the last game action. Returns the action which is undone.
     *
     * @return The undone action.
     */
    virtual model::GameAction undoLastAction();

    /**
     * Undoes the last turn. Returns the score to be reset.
     *
     * @return The score to be removed from the game score.
     */
    virtual int undoLastTurn();

    /**
     * Undoes the last game action. Returns the action which is redone.
     *
     * @return The redone action.
     */
    virtual model::GameAction redoLastAction();

    /**
     * Undoes the last turn. Returns the score to be re-added.
     *
     * @return The score to be added to the game score.
     */
    virtual int redoLastTurn();

    /**
     * Clears the buffer of actions.
     */
    virtual void clear();

    /**
     * Checks whether an undo is possible, meaning that there is an action in the buffer.
     *
     * @return True if possible.
     */
    virtual bool undoPossible() const;

    /**
     * Checks whether a redo is possible, meaning that there is an action in the buffer.
     *
     * @return True if possible.
     */
    virtual bool redoPossible() const;

private:

    /**
     * The recently performed game action.
     */
    std::vector<model::GameAction> actions;

    /**
     * The recently undone actions.
     */
    std::vector<model::GameAction> redoActions;

    /**
     * A pointer to the game field.
     */
    model::GameField* theField;

};

}//namespace controller

#endif // CONTROLLER_GAMEACTIONCONTROLLER_H

#ifndef MODEL_GAMEFIELD_H
#define MODEL_GAMEFIELD_H

//custom includes
#include "Model.FieldPosition.hpp"
#include "Model.Ball.hpp"

//global includes
#include <string>
#include <ctime>
#include <vector>
#include <assert.h>
#include <iostream>


namespace model
{

class GameField
{

public:

    /**
     * Creates a new game field of the given dimension.
     *
     * @param dimx The number of fields on the x-axis.
     * @param dimy The number of fields on the y-axis.
     */
    GameField(int dimx, int dimy);
    virtual ~GameField();

    /**
     * The neighborhood types.
     */
    enum Neighbour { Topleft, Topmiddle, Topright, Left, Middle, Right, BottomLeft, BottomMiddle, BottomRight};


    /**
     * Returns the ball at the given field position.
     *
     * @param pos The position.
     * @return The ball.
     */
    virtual model::Ball getBallAt(model::FieldPosition pos) const;

    /**
     * Returns the ball at the given field position.
     *
     * @param x The x-position.
     * @param y The y-position.
     * @return  The ball.
     */
    virtual model::Ball getBallAt(int x, int y) const;

    /**
     * Returns all neighbours of the field position.
     *
     * @param pos The position.
     * @return All neighbours.
     */
    virtual std::vector<model::Ball> getNeighbours(model::FieldPosition pos) const;

    /**
     * Returns the neighbour of the field position in the defined direction.
     *
     * @param pos The position.
     * @param neighbour The neighbourhood direction.
     * @return The ball.
     */
    virtual model::Ball getNeighbourAt(model::FieldPosition pos, Neighbour neighbour) const;

    /**
     * Sets a ball at the given field position.
     *
     * @param pos The position.
     * @param ball The ball.
     * @return True if possible.
     */
    virtual bool setBallAt(model::FieldPosition pos, model::Ball ball);

    /**
     * Removes the ball at the given field position.
     *
     * @param pos The position.
     * @return The removed ball. Invalid one if no ball at the given position.
     */
    virtual model::Ball removeBallAt(model::FieldPosition pos);

    /**
     * Returns all empty fields.
     *
     * @return The empty fields.
     */
    virtual std::vector<model::FieldPosition> getEmptyFields() const;

    /**
     * Returns the path between the two given positions. If no path is available the second position will not occur in the path.
     *
     * @param pos1 The first position.
     * @param pos2 The second position.
     * @return The path.
     */
    virtual std::vector<model::FieldPosition> getPath(model::FieldPosition pos1, model::FieldPosition pos2) const;

    /**
     * Clears the game field.
     */
    virtual void clear();

    /**
     * Returns the position of the neighbour.
     *
     * @param pos The position.
     * @param neighbour The neighbourhood direction.
     * @return The field position of the given neighbour.
     */
    virtual model::FieldPosition getPositionOfNeighbour(model::FieldPosition pos, Neighbour neighbour) const;

    /**
     * Returns the field dimension in x-direction.
     *
     * @return The x-dimension.
     */
    virtual int getDimensionX() const;

    /**
     * Returns the field dimension in y-direction.
     *
     * @return The y-dimension.
     */
    virtual int getDimensionY() const;

private:

    /**
     * The x-dimension.
     */
    int dimx;

    /**
     * The y-dimension.
     */
    int dimy;

    /**
     * All registered balls.
     */
    std::vector<model::Ball> entries;
};

}//namespace model


#endif // MODEL_GAMEFIELD_H

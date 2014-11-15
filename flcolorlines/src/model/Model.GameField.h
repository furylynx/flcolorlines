#ifndef MODEL_GAMEFIELD_H
#define MODEL_GAMEFIELD_H

#include <vector>
#include "Model.FieldPosition.h"
#include "Model.Ball.h"

namespace model{

class GameField{

public:

    GameField(int dimx, int dimy);
    ~GameField();

    enum Neighbour { Topleft, Topmiddle, Topright, Left, Middle, Right, BottomLeft, BottomMiddle, BottomRight};


    model::Ball getBallAt(model::FieldPosition pos) const;
    model::Ball getBallAt(int x, int y) const;

    std::vector<model::Ball> getNeighbours(model::FieldPosition pos) const;
    model::Ball getNeighbourAt(model::FieldPosition pos, Neighbour neighbour) const;

    bool setBallAt(model::FieldPosition pos, model::Ball ball);
    model::Ball removeBallAt(model::FieldPosition pos);

    std::vector<model::FieldPosition> getEmptyFields() const;

    std::vector<model::FieldPosition> getPath(model::FieldPosition pos1, model::FieldPosition pos2) const;

    void clear();

    static model::FieldPosition getPositionOfNeighbour(model::FieldPosition pos, Neighbour neighbour);

    int getDimensionX() const;
    int getDimensionY() const;

private:
    int dimx;
    int dimy;

    std::vector<model::Ball> entries;
};
}


#endif // MODEL_GAMEFIELD_H

#include <assert.h>
#include <iostream>

#include "Model.GameField.h"


using namespace model;

GameField::GameField(int dimx, int dimy){
    this->dimx = dimx;
    this->dimy = dimy;

    model::Ball null;
    null.isNull = true;
    null.outOfField = false;

    for (int i=1; i<=dimx*dimy;i++)
        entries.push_back(null);
}

GameField::~GameField()
{ }

model::Ball GameField::getBallAt(model::FieldPosition pos) const{

    if (pos.posX <0 || pos.posX >= dimx || pos.posY < 0 || pos.posY >= dimy)
    {
        model::Ball ret;
        ret.isNull = true;
        ret.outOfField = true;

        return ret;
    }

    return entries[(pos.posY*dimx+pos.posX)];
}

model::Ball GameField::getBallAt(int x, int y) const{
    model::FieldPosition pos;
    pos.posX = x;
    pos.posY = y;

    return getBallAt(pos);
}

bool GameField::setBallAt(model::FieldPosition pos, model::Ball ball){

    assert(pos.posX >= 0 );
    assert(pos.posX < dimx);
    assert(pos.posY >= 0);
    assert(pos.posY < dimy);

//    assert(!(pos.posX <0 || pos.posX >= dimx || pos.posY < 0 || pos.posY >= dimy));

    if (!getBallAt(pos).isNull)
        return false;

    entries[(pos.posY*dimx+pos.posX)] = ball;
    return true;
}

model::Ball GameField::removeBallAt(model::FieldPosition pos){

    assert(pos.posX >=0 );
    assert(pos.posX < dimx);
    assert(pos.posY >= 0);
    assert(pos.posY < dimy);

    if ((pos.posX <0 || pos.posX >= dimx || pos.posY < 0 || pos.posY >= dimy))
        int a = 0;

    model::Ball ret = getBallAt(pos);

    model::Ball ball;
    ball.isNull = true;
    ball.outOfField = false;
    entries[(pos.posY*dimx+pos.posX)] = ball;//TODO...

    return ret;
}


model::Ball GameField::getNeighbourAt(model::FieldPosition pos, Neighbour neighbour) const{


    return getBallAt(GameField::getPositionOfNeighbour(pos, neighbour));
}

std::vector<Ball> GameField::getNeighbours(model::FieldPosition pos) const{

    std::vector<Ball> neighbours;

    for (int i = Topleft; i<= BottomRight; i++)
        neighbours.push_back(getNeighbourAt(pos,static_cast<Neighbour>(i)));

    return neighbours;
}

std::vector<model::FieldPosition> GameField::getEmptyFields() const{

    std::vector<model::FieldPosition> ret;

    for (int i = 0; i< dimx; i++)
        for (int j=0; j< dimy;j++){
            model::FieldPosition pos; pos.posX = i; pos.posY=j;
            if (getBallAt(pos).isNull)
                ret.push_back(pos);
        }

    return ret;
}

void GameField::clear(){

    entries.clear();

    model::Ball null;
    null.isNull = true;
    null.outOfField = false;

    for (int i=1; i<=dimy*dimy;i++)
        entries.push_back(null);
}

model::FieldPosition GameField::getPositionOfNeighbour(FieldPosition pos, Neighbour neighbour){

    model::FieldPosition ballAt;
    if (neighbour == Topleft){
        ballAt.posX = pos.posX-1;
        ballAt.posY = pos.posY+1;
    }
    if (neighbour == Topmiddle){
        ballAt.posX = pos.posX;
        ballAt.posY = pos.posY+1;
    }

    if (neighbour == Topright){
        ballAt.posX = pos.posX+1;
        ballAt.posY = pos.posY+1;
    }
    if (neighbour == Left){
        ballAt.posX = pos.posX-1;
        ballAt.posY = pos.posY;
    }
    if (neighbour == Middle){
        ballAt = pos;
    }
    if (neighbour == Right){
        ballAt.posX = pos.posX+1;
        ballAt.posY = pos.posY;
    }
    if (neighbour == BottomLeft){
        ballAt.posX = pos.posX-1;
        ballAt.posY = pos.posY-1;
    }
    if (neighbour == BottomMiddle){
        ballAt.posX = pos.posX;
        ballAt.posY = pos.posY-1;
    }
    if (neighbour == BottomRight){
        ballAt.posX = pos.posX+1;
        ballAt.posY = pos.posY-1;
    }

    return ballAt;
}

std::vector<model::FieldPosition> GameField::getPath(model::FieldPosition pos1, model::FieldPosition pos2) const{

    std::vector<model::FieldPosition> vec;
    model::FieldPosition currentNode;

    model::FieldPosition visitedNodes[dimx][dimy];

    //probably not necessary since false is default initialization
    for (int i = 0; i< dimx;i++)
        for (int j = 0; j< dimy; j++)
            visitedNodes[i][j].posX = -1;

    vec.push_back(pos1);
    visitedNodes[pos1.posX][pos1.posY].posX = -2;

    while (!vec.empty())
    {
        currentNode = vec.front();
        vec.erase(vec.begin());

        if (currentNode.posX == pos2.posX && currentNode.posY == pos2.posY){

            //should be checked
            std::vector<model::FieldPosition> ret;

            while (visitedNodes[currentNode.posX][currentNode.posY].posX != -2){
                ret.insert(ret.begin(),currentNode);
                currentNode = visitedNodes[currentNode.posX][currentNode.posY];
            }
            ret.insert(ret.begin(),currentNode);

            return ret;
        }

        for (int i= Topmiddle;i<=BottomMiddle; i+=2){//look at all four neighbours

            model::FieldPosition neighbour = GameField::getPositionOfNeighbour(currentNode, static_cast<model::GameField::Neighbour>(i));

            if (getBallAt(neighbour).isNull && !getBallAt(neighbour).outOfField && visitedNodes[neighbour.posX][neighbour.posY].posX == -1){

                vec.push_back(neighbour);
                visitedNodes[neighbour.posX][neighbour.posY] = currentNode;

            }

        }
    }

    std::vector<model::FieldPosition> ret;
    ret.push_back(pos1);

    return ret;

}

int GameField::getDimensionX() const{
    return dimx;
}

int GameField::getDimensionY() const{
    return dimy;
}


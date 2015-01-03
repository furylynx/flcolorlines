#include "Model.Color.hpp"

using namespace model;

int Color::getColorB() const{

    return ((color & 255));
}

int Color::getColorG() const{

    return ((color & 65280)>>8);
}

int Color::getColorR() const{

    return ((color & 16711680) >> 16);
}

int Color::getColorA() const{

    return ((color & 4278190080) >> 24);
}

void Color::setColor(int red, int green, int blue, int alpha){

    color = (alpha << 24) + (red << 16) + (green << 8)+ blue;
}

void Color::setColor(unsigned int c){

    unsigned int red = ((c & 4278190080) >> 24);
    unsigned int green = ((c & 16711680) >> 16);
    unsigned int blue = ((c & 65280)>>8);
    unsigned int alpha = (c & 255);

    setColor(red,green,blue,alpha);
}

void Color::setColor(DefinedColor c){

    unsigned int col;
    //check the color
    if (c == RED)
        col = 0xd72121ff;
    else
        if (c==BLUE)
            col= 0x4237d4ff;
        else
            if (c == GREEN)
                col=0x0d7d17ff;
            else
                if(c == YELLOW)
                    col = 0xe1df40ff;
                else
                    if (c==ORANGE)
                        col= 0xef962eff;
                    else
                        if (c == LIGHTBLUE)
                            col= 0x1cc7c9ff;
                        else
                            if ( c== PURPLE)
                                col= 0x920eaeff;
                            else
                                if ( c== DARKRED)
                                    col= 0x681111ff;
                                else
                                    if ( c== DARKGREEN)
                                        col= 0x0a4110ff;
                                    else
                                        if ( c== DARKBLUE)
                                            col= 0x19224bff;
                                        else
                                            if ( c== LIGHTGREEN)
                                                col= 0x39c940ff;
                                            else
                                                if ( c== BROWN)
                                                    col= 0x793609ff;
                                                else
                                                    col= 0;

    unsigned int red = ((col & 4278190080) >> 24);
    unsigned int green = ((col & 16711680) >> 16);
    unsigned int blue = ((col & 65280)>>8);
    unsigned int alpha = (col & 255);

    setColor(red,green,blue,alpha);
}

bool Color::operator==(Color const& c2){

    return this->color == c2.color;

}


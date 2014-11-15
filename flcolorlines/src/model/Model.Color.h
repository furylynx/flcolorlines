#ifndef MODEL_COLOR_H
#define MODEL_COLOR_H

namespace model{

struct Color{

    enum DefinedColor {RED=0, BLUE, GREEN, YELLOW, ORANGE, LIGHTBLUE, PURPLE, LIGHTGREEN, BROWN, DARKRED, DARKGREEN, DARKBLUE, AMOUNT_DEFINED_COLORS};

    unsigned int color;

    int getColorR() const;
    int getColorG() const;
    int getColorB() const;
    int getColorA() const;

    void setColor(int red, int green, int blue, int alpha);
    void setColor(unsigned int);
    void setColor(DefinedColor c);

    bool operator==(Color const& c2);
//    bool operator==(Color const& c1, Color const& c2);


};

}

#endif // MODEL_COLOR_H

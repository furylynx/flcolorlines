#ifndef MODEL_COLOR_H
#define MODEL_COLOR_H

//custom includes
//...

//global includes
//...

namespace model
{

struct Color
{
    /**
     * Defined colors that can be used.
     */
    enum DefinedColor {RED=0, BLUE, GREEN, YELLOW, ORANGE, LIGHTBLUE, PURPLE, LIGHTGREEN, BROWN, DARKRED, DARKGREEN, DARKBLUE, AMOUNT_DEFINED_COLORS};

    unsigned int color;

    /**
     * Returns the red part of the color.
     *
     * @return The red part.
     */
    int getColorR() const;

    /**
     * Returns the green part of the color.
     *
     * @return The green part.
     */
    int getColorG() const;

    /**
     * Returns the blue part of the color.
     *
     * @return The blue part.
     */
    int getColorB() const;

    /**
     * Returns the alpha part of the color.
     *
     * @return The alpha channel.
     */
    int getColorA() const;

    /**
     * Sets the RGBA color.
     *
     * @param red The red part.
     * @param green The green part.
     * @param blue The blue part.
     * @param alpha The alpha part.
     */
    void setColor(int red, int green, int blue, int alpha);

    /**
     * Sets the 32 bit color.
     *
     * @param c The color.
     */
    void setColor(unsigned int c);

    /**
     * Sets the color by the enum color value.
     *
     * @param c The defined color.
     */
    void setColor(DefinedColor c);

    /**
     * Compares this color value with the given one. Returns true if they are equal.
     *
     * @param c2 The color to be compared to.
     * @return True if equal.
     */
    bool operator==(Color const& c2);

};

}//namespace model

#endif // MODEL_COLOR_H

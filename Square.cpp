#include "Square.hpp"
Square::Square(QColor color)
{
    setBrush(color);
    setZValue(-1);
    setRect(0, 0, 35, 35);
}

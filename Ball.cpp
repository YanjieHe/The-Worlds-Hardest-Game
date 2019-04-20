#include "Ball.hpp"
#include <QDebug>
Ball::Ball(QVector<QPointF> points)
    : QGraphicsEllipseItem(nullptr), points{points}, index{0}
{
    setRect(0, 0, 15, 15);
    setBrush(Qt::blue);
    setPos(points.front());
    setPen(QPen(Qt::black, 3));
}

void Ball::Move()
{
    if (index == 0 && change == -1)
    {
        change = 1;
    }
    if (index == points.size() - 1 && change == 1)
    {
        change = -1;
    }
    index = index + change;
    setPos(points[index]);
}

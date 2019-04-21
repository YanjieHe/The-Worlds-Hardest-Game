#include "Player.hpp"
#include "Ball.hpp"
#include "Square.hpp"
#include <QDebug>
#include <QGraphicsView>
#include <QKeyEvent>
Player::Player() : QGraphicsRectItem(nullptr), start{QPointF(0, 0)}, death{0}
{
    setRect(0, 0, 24, 24);
    setPos(start);
    setBrush(Qt::red);
    setPen(QPen(Qt::black, 5));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Player::keyPressEvent(QKeyEvent* event)
{
    if (pressingKeys.find(event->key()) == pressingKeys.end())
    {
        pressingKeys.insert({event->key()});
    }
}

void Player::keyReleaseEvent(QKeyEvent* event)
{
    if (pressingKeys.find(event->key()) != pressingKeys.end())
    {
        pressingKeys.remove(event->key());
    }
}

void Player::focusOutEvent(QFocusEvent*)
{
    setFocus();
}

bool Player::CanMove(qreal x, qreal y)
{
    for (auto line : lines)
    {
        qreal x1 = line->line().x1();
        qreal x2 = line->line().x2();
        qreal y1 = line->line().y1();
        qreal y2 = line->line().y2();
        if ((x1 <= x && x <= x2) || (y1 <= y && y <= y2))
        {
            qreal d1 = (y1 - y2) * this->x() - (x1 - x2) * this->y() + x1 * y2 -
                       x2 * y2 - y1 * x2 + y2 * x2;
            qreal d2 = (y1 - y2) * x - (x1 - x2) * y + x1 * y2 - x2 * y2 -
                       y1 * x2 + y2 * x2;
            if (d1 * d2 <= 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool Player::CheckFourCorners(qreal x, qreal y)
{
    if (!CanMove(x, y))
    {
        return false;
    }
    else if (!CanMove(x, y + rect().width()))
    {
        return false;
    }
    else if (!CanMove(x + rect().width(), y))
    {
        return false;
    }
    else if (!CanMove(x + rect().width(), y + rect().width()))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Player::DetectMove()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        auto item = colliding_items[i];
        if (typeid(*item) == typeid(Ball))
        {
            setPos(start);
            death++;
        }
    }
    if (pressingKeys.find(Qt::Key_Left) != pressingKeys.end())
    {
        if (pos().x() > 0 && CheckFourCorners(x() - 2, y()))
        {
            setPos(x() - 2, y());
        }
    }
    if (pressingKeys.find(Qt::Key_Right) != pressingKeys.end())
    {
        if (pos().x() + rect().width() < 800 && CheckFourCorners(x() + 2, y()))
        {
            setPos(x() + 2, y());
        }
    }
    if (pressingKeys.find(Qt::Key_Up) != pressingKeys.end())
    {
        if (pos().y() > 0 && CheckFourCorners(x(), y() - 2))
        {
            setPos(x(), y() - 2);
        }
    }
    if (pressingKeys.find(Qt::Key_Down) != pressingKeys.end())
    {
        if (pos().y() + rect().width() < 800 && CheckFourCorners(x(), y() + 2))
        {
            setPos(x(), y() + 2);
        }
    }
}

bool Player::TryMove(int direction)
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        auto item = colliding_items[i];
        if (typeid(*item) == typeid(Ball))
        {
            setPos(start);
            death++;
        }
    }
    if (direction == 0)
    {
        if (pos().y() > 0 && CheckFourCorners(x(), y() - 2))
        {
            setPos(x(), y() - 2);
            return true;
        }
    }
    else if (direction == 1)
    {
        if (pos().y() + rect().width() < 800 && CheckFourCorners(x(), y() + 2))
        {
            setPos(x(), y() + 2);
            return true;
        }
    }
    else if (direction == 2)
    {
        if (pos().x() > 0 && CheckFourCorners(x() - 2, y()))
        {
            setPos(x() - 2, y());
            return true;
        }
    }
    else if (direction == 3)
    {
        if (pos().x() + rect().width() < 800 && CheckFourCorners(x() + 2, y()))
        {
            setPos(x() + 2, y());
            return true;
        }
    }
    return false;
}

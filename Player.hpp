#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <QGraphicsRectItem>
#include <QObject>
#include <QSet>
class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
  public:
    QPointF start;
    QVector<QGraphicsLineItem*> lines;
    int death;
    QSet<int> pressingKeys;

    Player();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

    bool CanMove(qreal x, qreal y);
    bool CheckFourCorners(qreal x, qreal y);
    void DetectMove();
    bool TryMove(int direction);
};

#endif // PLAYER_HPP

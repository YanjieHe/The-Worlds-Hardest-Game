#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <QGraphicsRectItem>
#include <QObject>
#include <QSet>
#include <QTimer>
class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
  public:
    Player();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
    QPointF start;
    QVector<QGraphicsLineItem*> lines;

    QSet<int> pressingKeys;
    QTimer timer;
    bool CanMove(qreal x, qreal y);
    bool CheckFourCorners(qreal x, qreal y);
  private slots:
    void Move();
};

#endif // PLAYER_HPP

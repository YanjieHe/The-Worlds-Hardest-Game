#ifndef BALL_HPP
#define BALL_HPP
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QObject>
#include <QTimer>

class Ball : public QObject, public QGraphicsEllipseItem {
  Q_OBJECT
 public:
  Ball(QVector<QPointF> points);
  QVector<QPointF> points;
  int index;
  int change = 1;

  void Move();
};

#endif  // BALL_HPP

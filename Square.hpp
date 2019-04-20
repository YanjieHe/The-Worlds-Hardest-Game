#ifndef SQUARE_HPP
#define SQUARE_HPP
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QObject>
#include <QSet>
#include <QTimer>
class Square : public QObject, public QGraphicsRectItem {
  Q_OBJECT
 public:
  Square(QColor color);
};

#endif  // SQUARE_HPP

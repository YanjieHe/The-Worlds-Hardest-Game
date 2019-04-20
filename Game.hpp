#ifndef GAME_HPP
#define GAME_HPP
#include "Ball.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "State.hpp"
#include <QGraphicsView>
#include <QJsonObject>
#include <QVector>
class Game : public QGraphicsView
{
    Q_OBJECT
  public:
    Game(QWidget* parent = nullptr);
    QGraphicsScene scene;
    Player player;
    QVector<Ball*> balls;
    QVector<Square*> squares;
    QTimer timer;
    QTimer playerTimer;
    ~Game();
    void DrawBorder();
    void LoadSettings(QString path);
    void MakeSquare(QColor color, int x, int y);
    void MakeBall(QVector<QPointF> points);
    void LoadGreenSquares(QJsonObject& object);
    void LoadNormalSquares(QJsonObject& object);
    State CreateState();
    static QColor green;
    static QColor gray;
    static QColor light;
    const int width = 35;
  public slots:
    void MoveBalls();
};

#endif // GAME_HPP
#ifndef GAME_HPP
#define GAME_HPP
#include "AI.hpp"
#include "Ball.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Square.hpp"
#include "State.hpp"
#include <QGraphicsView>
#include <QJsonObject>
#include <QMap>
#include <QPoint>
#include <QSet>
#include <QVector>

class Game : public QGraphicsView
{
    Q_OBJECT
  public:
    QGraphicsScene scene;
    Player player;
    QVector<Ball*> balls;
    QVector<Square*> squares;
    QTimer ballsTimer;
    QTimer playerTimer;
    AI ai;
    State previousState;
    int previousDeath = -1;
    Board board;

    Game(QWidget* parent = nullptr);
    ~Game();
    void SetBackground();
    void DrawBorder();
    void LoadSettings(QString path);
    void MakeSquare(QColor color, int x, int y);
    void MakeBall(QVector<QPointF> points);
    void LoadGreenSquares(QJsonObject& object);
    void LoadNormalSquares(QJsonObject& object);
    State CreateState();
    void Initialize();

    static QColor green;
    static QColor gray;
    static QColor light;
    const int width = 35;
  public slots:
    void Update();
    void MoveBalls();
    void MovePlayer();
    void MakeDecision();
};

#endif // GAME_HPP

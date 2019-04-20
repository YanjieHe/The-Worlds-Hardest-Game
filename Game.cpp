#include "Game.hpp"
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

QColor Game::green(164, 254, 163);
QColor Game::gray(247, 247, 255);
QColor Game::light(221, 221, 255);

Game::Game(QWidget*) : timer(this), playerTimer(this)
{
    SetBackground();
    LoadSettings("test.json");
    DrawBorder();

    connect(&timer, SIGNAL(timeout()), this, SLOT(MoveBalls()));
    timer.start(15);

    connect(&playerTimer, SIGNAL(timeout()), this, SLOT(MakeDecision()));
    playerTimer.start(15);
}

Game::~Game()
{
    for (Ball* ball : balls)
    {
        delete ball;
    }
}

void Game::SetBackground()
{
    scene.setSceneRect(0, 0, 800, 600);
    setScene(&scene);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);
    scene.addItem(&player);
    scene.setBackgroundBrush(QColor(179, 179, 255));
}

void Game::DrawBorder()
{
    std::unordered_map<int, std::unordered_set<int>> positions;
    for (Square* square : squares)
    {
        int x = static_cast<int>(square->x());
        int y = static_cast<int>(square->y());
        if (positions.find(x) != positions.end())
        {
            positions[x].insert(y);
        }
        else
        {
            positions.insert({x, {y}});
        }
    }
    auto exists = [&positions](int x, int y) {
        if (positions.find(x) != positions.end())
        {
            return positions[x].find(y) != positions[x].end();
        }
        else
        {
            return false;
        }
    };
    QVector<QGraphicsLineItem*> lines;
    for (Square* square : squares)
    {
        int width = static_cast<int>(square->rect().width());
        int x	 = static_cast<int>(square->x());
        int y	 = static_cast<int>(square->y());
        QPen pen(Qt::black);
        pen.setWidth(5);
        if (!exists(x - width, y))
        {
            lines << scene.addLine(x, y, x, y + width, pen);
        }
        if (!exists(x + width, y))
        {
            lines << scene.addLine(x + width, y, x + width, y + width, pen);
        }
        if (!exists(x, y - width))
        {
            lines << scene.addLine(x, y, x + width, y, pen);
        }
        if (!exists(x, y + width))
        {
            lines << scene.addLine(x, y + width, x + width, y + width, pen);
        }
    }
    player.lines = lines;
}

void Game::LoadSettings(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString json = stream.readAll();
        qDebug() << "json" << json;
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(json.toUtf8(), &error);
        if (!document.isNull() && (error.error == QJsonParseError::NoError))
        {
            // successfully parsed the settings
            if (document.isObject())
            {
                QJsonObject object = document.object();
                LoadGreenSquares(object);
                LoadNormalSquares(object);
                QJsonArray playerStartPosition =
                    object.value("Player Start Position").toArray();
                player.setPos(
                    QPointF(playerStartPosition.at(0).toInt() * width,
                            playerStartPosition.at(1).toInt() * width));
                player.start = player.pos();
                QJsonArray verticalBalls =
                    object.value("Vertical Ball").toArray();
                for (int i = 0; i < verticalBalls.size(); i++)
                {
                    auto position = verticalBalls.at(i).toArray();
                    int startX	= position.at(0).toInt();
                    int startY	= position.at(1).toInt();
                    int endX	  = position.at(2).toInt();
                    int endY	  = position.at(3).toInt();
                    qDebug() << startX << startY << endX << endY;
                    int step = endY > startY ? 3 : -3;
                    if (startX != endX)
                    {
                        qDebug() << "vertical ball error";
                    }
                    else
                    {
                        QVector<QPointF> points;
                        if (step > 0)
                        {
                            for (int y = startY * width; y <= endY * width;
                                 y	 = y + step)
                            {
                                points.push_back(
                                    QPointF(startX * width + width / 2.0 - 7.5,
                                            y + width / 2.0 - 7.5));
                            }
                        }
                        else
                        {
                            for (int y = startY * width; y >= endY * width;
                                 y	 = y + step)
                            {
                                points.push_back(
                                    QPointF(startX * width + width / 2.0 - 7.5,
                                            y + width / 2.0 - 7.5));
                            }
                        }
                        MakeBall(points);
                    }
                }
            }
            else
            {
                qDebug() << "not object";
            }
        }
        else
        {
            qDebug() << "json format error";
        }
    }
}

void Game::MakeSquare(QColor color, int x, int y)
{
    Square* square = new Square(color);
    square->setPos(x, y);
    square->setPen(Qt::NoPen);
    scene.addItem(square);
    squares.push_back(square);
}

void Game::MakeBall(QVector<QPointF> points)
{
    Ball* ball = new Ball(points);
    balls.push_back(ball);
    scene.addItem(ball);
}

void Game::LoadGreenSquares(QJsonObject& object)
{
    QJsonArray greenSquares = object.value("Green Squares").toArray();
    for (int i = 0; i < greenSquares.size(); i++)
    {
        QJsonArray position = greenSquares.at(i).toArray();
        int x				= position.at(0).toInt();
        int y				= position.at(1).toInt();
        MakeSquare(green, x * width, y * width);
    }
}

void Game::LoadNormalSquares(QJsonObject& object)
{
    QJsonArray normalSquares = object.value("Normal Squares").toArray();
    for (int i = 0; i < normalSquares.size(); i++)
    {
        QJsonArray position = normalSquares.at(i).toArray();
        int x				= position.at(0).toInt();
        int y				= position.at(1).toInt();
        MakeSquare((x + y) % 2 == 0 ? gray : light, x * width, y * width);
    }
}

State Game::CreateState()
{
    std::vector<double> positions;
    positions.push_back(player.x());
    positions.push_back(player.y());
    for (Ball* ball : balls)
    {
        positions.push_back(ball->x());
        positions.push_back(ball->y());
    }
    return State(positions, {0, 0, 0, 0});
}

void Game::MoveBalls()
{
    for (Ball* ball : balls)
    {
        ball->Move();
    }
}

void Game::MakeDecision()
{
    State state = CreateState();
}

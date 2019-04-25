#ifndef BOARD_HPP
#define BOARD_HPP
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using std::cout;
using std::endl;

class Board
{
  public:
    class Point
    {
      public:
        int x;
        int y;
        Point() : x{0}, y{0}
        {
        }
        Point(int x, int y) : x{x}, y{y}
        {
        }
    };

    class Ball
    {
      public:
        Point position;
        int height;
        int width;
        Ball() : height{0}, width{0}
        {
        }
        Ball(Point position, int height, int width)
            : position{position}, height{height}, width{width}
        {
        }
    };

    class Square
    {
      public:
        Point position;
        int height;
        int width;
        Square() : height{height}, width{width}
        {
        }
        Square(Point position, int height, int width)
            : position{position}, height{height}, width{width}
        {
        }
    };

    class Line
    {
      public:
        Point start;
        Point end;
        Line() : start{start}, end{end}
        {
        }
        Line(int x1, int y1, int x2, int y2) : start(x1, y1), end(x2, y2)
        {
        }
        Line(Point start, Point end) : start{start}, end{end}
        {
        }
    };
    class Track
    {
      public:
        std::vector<Point> points;
        int index = -1;
        Track()
        {
        }
        Track(std::vector<Point> points) : points{points}
        {
        }
        const Point& Next()
        {
            index = (index + 1) % static_cast<int>(points.size());
            return points.at(index);
        }
    };

    std::vector<Ball> balls;
    std::vector<Line> lines;
    std::vector<Track> tracks;
    Square square;
    const int step = 2;
    Point target;
    Board();
    std::vector<std::tuple<double, int>> Decide();
    double Search(Square square, std::vector<Ball> balls,
                  std::vector<int> indexList,
                  std::vector<std::vector<Point>>& points, int depth,
                  int maxDepth, double bound);
    static bool SquareBallOverlap(const Square& square, const Ball& ball);
    static bool SquareLineOverlap(const Square& square, const Line& line);
    static void MoveBalls(std::vector<Ball>& balls, std::vector<int>& indexList,
                          std::vector<std::vector<Point>>& points);
};
template <> struct std::hash<Board::Point>
{
    std::size_t operator()(const Board::Point& point) const
    {
        return point.x ^ point.y;
    }
};
#endif // BOARD_HPP

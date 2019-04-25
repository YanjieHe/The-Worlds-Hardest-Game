#include "Board.hpp"
const int step = 5;
Board::Board()
{
}

std::vector<std::tuple<double, int>> Board::Decide()
{
    std::vector<std::tuple<double, int>> choices;
    choices.reserve(4);
    static int xMoves[] = {0, 0, -1, +1}; // up, down, left, right
    static int yMoves[] = {-1, +1, 0, 0}; // up, down, left, right
    std::vector<int> indexList(tracks.size());
    std::vector<std::vector<Point>> points(tracks.size());
    for (int i = 0; i < static_cast<int>(tracks.size()); i++)
    {
        indexList.at(i) = tracks.at(i).index;
        points.at(i)	= tracks.at(i).points;
    }
    auto pow2 = [](double x) { return x * x; };
    double d1 = pow2(square.position.x + xMoves[1] * 2 * 2 - target.x) +
                pow2(square.position.y + yMoves[1] * 2 - target.y);
    double d2 = pow2(square.position.x + xMoves[3] * 2 - target.x) +
                pow2(square.position.y + yMoves[3] * 2 * 2 - target.y);
    double upperBound = std::max(1 / std::sqrt(d1), 1 / std::sqrt(d2));
    for (int i = 0; i < 4; i++)
    {
        Square t = square;
        t.position.x += xMoves[i] * step;
        t.position.y += yMoves[i] * step;
        choices.push_back(
            {Search(t, balls, indexList, points, 0, 8, upperBound), i});
        cout << std::get<1>(choices.back()) << ": "
             << std::get<0>(choices.back()) << endl;
    }
    std::sort(choices.begin(), choices.end(),
              [](auto& x, auto& y) { return std::get<0>(x) > std::get<0>(y); });
    return choices;
}

double Board::Search(Board::Square square, std::vector<Board::Ball> balls,
                     std::vector<int> indexList,
                     std::vector<std::vector<Board::Point>>& points, int depth,
                     int maxDepth, double bound)
{
    //    cout << square.position.x << ", " << square.position.y << endl;
    MoveBalls(balls, indexList, points);
    for (const auto& ball : balls)
    {
        if (SquareBallOverlap(square, ball))
        {
            //            cout << "square ball overlap" << endl;
            return -100;
        }
    }
    for (const auto& line : lines)
    {
        if (SquareLineOverlap(square, line))
        {
            //            cout << "square line overlap" << endl;
            return -100;
        }
    }
    if (depth >= maxDepth)
    {
        double dx		= square.position.x - target.x;
        double dy		= square.position.y - target.y;
        double distance = std::sqrt(dx * dx + dy * dy);
        return 1.0 / distance;
    }
    else
    {
        static int xMoves[] = {0, +1, 0, -1}; // down, right, up, left
        static int yMoves[] = {+1, 0, -1, 0}; // down, right, up, left
        double sum			= 0.0;
        for (int i = 0; i < 4; i++)
        {
            Square t = square;
            t.position.x += xMoves[i] * step;
            t.position.y += yMoves[i] * step;
            //            if (i == 0)
            //            {
            //                max = Search(t, balls, indexList, points, depth +
            //                1, maxDepth,
            //                             bound);
            //            }
            //            else
            //            {
            //                max = std::max(max, Search(t, balls, indexList,
            //                points,
            //                                           depth + 1, maxDepth,
            //                                           bound));
            //            }
            sum = sum + Search(t, balls, indexList, points, depth + 1, maxDepth,
                               bound);
        }
        return sum / 4.0;
    }
}

bool Board::SquareBallOverlap(const Board::Square& square,
                              const Board::Ball& ball)
{
    int x1 = square.position.x;
    int y1 = square.position.y;
    int x2 = square.position.x + square.width;
    int y2 = square.position.y + square.height;

    int x3 = ball.position.x;
    int y3 = ball.position.y;
    int x4 = ball.position.x + ball.width;
    int y4 = ball.position.y + ball.height;

    bool case1 = x1 < x4 && x3 < x2 && y1 < y4 && y3 < y2;
    bool case2 = x3 < x2 && x1 < x4 && y3 < y2 && y1 < y4;
    bool case3 = x3 < x2 && y3 < y2 && x1 < x4 && y1 < y4;
    bool case4 = x1 < x4 && x3 < x2 && y1 < y4 && y3 < y2;

    if (case1 || case2 || case3 || case4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::SquareLineOverlap(const Board::Square& square,
                              const Board::Line& line)
{
    int x1 = square.position.x;
    int y1 = square.position.y;
    int x2 = square.position.x + square.width;
    int y2 = square.position.y + square.height;

    int x3 = line.start.x;
    int y3 = line.start.y;
    int x4 = line.end.x;
    int y4 = line.end.y;

    bool case1 = x1 < x4 && x3 < x2 && y1 < y4 && y3 < y2;
    bool case2 = x3 < x2 && x1 < x4 && y3 < y2 && y1 < y4;
    bool case3 = x3 < x2 && y3 < y2 && x1 < x4 && y1 < y4;
    bool case4 = x1 < x4 && x3 < x2 && y1 < y4 && y3 < y2;

    if (case1 || case2 || case3 || case4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Board::MoveBalls(std::vector<Board::Ball>& balls,
                      std::vector<int>& indexList,
                      std::vector<std::vector<Board::Point>>& points)
{
    for (int i = 0; i < static_cast<int>(balls.size()); i++)
    {
        indexList.at(i) =
            ((indexList.at(i)) % static_cast<int>(points.at(i).size()));
        balls.at(i).position = points.at(i).at(indexList.at(i));
    }
}

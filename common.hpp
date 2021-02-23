#ifndef COMMON_HPP
#define COMMON_HPP

#include <QString>
#include <QMap>
#include <QVector2D>

QString operator""_Q(const char *, size_t);

enum Move : int
{
    Left,
    Right,
    Up,
    Down
};

const static QMap<Move, QVector2D> MoveVector
{
    {Left, {0, -1}},
    {Right, {0, 1}},
    {Up, {-1, 0}},
    {Down, {1, 0}}
};

const static QMap<Move, QString> MoveLiteral
{
    {Left, "L"},
    {Right, "R"},
    {Up, "U"},
    {Down, "D"}
};

const static auto MoveFormat = "%0%1"_Q;

const static int ScrambleMovesCount = 50;

#endif // COMMON_HPP

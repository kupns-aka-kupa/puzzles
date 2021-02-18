#ifndef TABLE_HPP
#define TABLE_HPP

#include <QObject>
#include <QColor>
#include <array>

const int GRAY[3] = {0x31, 0x36, 0x3b};
const int BLACK[3] = {0x23, 0x26, 0x2a};
const int WHITE[3] = {0xef, 0xf0, 0xf1};

const int RED[3] = {0xce, 0x42, 0x50};
const int ORANGE[3] = {0xf5, 0x9e, 0x16};
const int BLUE[3] = {0x29, 0x80, 0xb9};
const int GREEN[3] = {0x26, 0x8C, 0x52};
const int MAGENTA[3] = {0xbd, 0x93, 0xf9};
const int PURPLE[3] = {0xf6, 0x76, 0xc0};

class Table
{
public:
    using Item = QPair<int, std::array<int, 3>>;
    using Row = QVector<Item>;
    using Iterator = Row::Iterator;

    Table() = default;
    explicit Table(int i, int j);

    Iterator rowIterator(int j);
    Iterator collumnIterator(int i);

private:
    static QColor calculateDelta(int i, int j);

private:
    QVector<Row> matrix;
    QColor delta;
};



#endif // TABLE_HPP

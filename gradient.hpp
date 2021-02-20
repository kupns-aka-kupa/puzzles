#ifndef GRADIENT_HPP
#define GRADIENT_HPP

#include <QGradient>
#include <QtAlgorithms>
#include <QMap>
#include <QPropertyAnimation>

class Gradient : public QLinearGradient
{
    using Base = QLinearGradient;
public:
    Gradient()
        : Base() { };

    Gradient(const QPointF &s, const QPointF &f)
        : Base(s, f) { };

    QColor getColor(qreal key) const;

private:
    Q_CONSTEXPR static qreal delta = 100.;
};

#endif // GRADIENT_HPP

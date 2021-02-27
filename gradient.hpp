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
    Gradient();
    Gradient(QRect rect);
    Gradient(const QPointF &start, const QPointF &finish);

    QColor getColor(qreal key) const;

private:
    Q_CONSTEXPR static qreal delta = 100.;
};

#endif // GRADIENT_HPP

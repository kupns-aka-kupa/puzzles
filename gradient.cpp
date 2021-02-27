#include "gradient.hpp"

Gradient::Gradient()
    : Base() { };

Gradient::Gradient(QRect rect)
    : Gradient(rect.topLeft(), rect.bottomRight()) { };

Gradient::Gradient(const QPointF &s, const QPointF &f)
    : Base(s, f) { };

QColor Gradient::getColor(qreal key) const
{
    QMap<qreal, QColor> map;
    QPropertyAnimation animation;

    key = qBound(key, 0., 1.);

    foreach(auto stop, stops())
    {
        map.insert(stop.first, stop.second);
    }

    if(map.contains(key))
    {
        return map.value(key);
    }

    animation.setEasingCurve(QEasingCurve::Linear);
    animation.setDuration(delta);

    foreach(qreal key, map.keys())
    {
        animation.setKeyValueAt(key, map.value(key));
    }

    animation.setCurrentTime(key * delta);
    return animation.currentValue().value<QColor>();
}

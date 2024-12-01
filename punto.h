#ifndef PUNTO_H
#define PUNTO_H

#include <QObject>
#include <QGraphicsEllipseItem>


class Punto : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    explicit Punto(int cellSize, QGraphicsItem *parent = nullptr);
};

#endif // PUNTO_H

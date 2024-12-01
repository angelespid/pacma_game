#include "punto.h"
#include <QBrush>

    Punto::Punto(int cellSize, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent) {
    setRect(0, 0, cellSize / 2, cellSize / 2); // Tamaño del punto
    setBrush(Qt::red);                      // Color amarillo
}

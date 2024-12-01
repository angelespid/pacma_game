#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>

class Bloque : public QGraphicsRectItem {
public:
    explicit Bloque(int tipo, int x, int y, int size);

    int getTipo() const; // Devuelve el tipo del bloque (0: camino, 1: pared)

private:
    int tipo; // Tipo del bloque: 0 para camino, 1 para pared
};

#endif // BLOQUE_H

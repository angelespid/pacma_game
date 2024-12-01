#ifndef LABERINTO_H
#define LABERINTO_H

#include <QGraphicsScene>
#include <QVector>
#include "bloque.h"

class Laberinto {
public:
    explicit Laberinto(QGraphicsScene *scene, int cellSize);
    void dibujarLaberinto(const QVector<QVector<int>> &mapa); // Genera el laberinto

private:
    QGraphicsScene *scene; // Escena para dibujar los elementos
    int cellSize;          // Tamaño de cada celda en píxeles
};

#endif // LABERINTO_H
